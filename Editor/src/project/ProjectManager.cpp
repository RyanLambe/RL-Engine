#include "ProjectManager.h"

#include <chrono>
#include <filesystem>

#include "../Editor.h"
#include "../tools/CodeManager.h"
#include "../windows/AssetBrowser.h"
#include "../windows/Console.h"

using namespace rl::ed;

ProjectManager* ProjectManager::projectManager = nullptr;

ProjectManager::ProjectManager()
{
    if (projectManager)
    {
        RL_LOG_ERROR("Cannot create multiple Project Managers.");
        return;
    }
    projectManager = this;
}

ProjectManager::~ProjectManager()
{
    Application::SetGameContext(nullptr);
}

bool ProjectManager::New(const std::string& name, const std::string& path)
{
    projectManager->projectName = name;
    projectManager->projectDir = path + "/" + name + "/";

    if (name.empty() || path.empty())
    {
        RL_LOG_ERROR("Name or Path not entered.");
        return false;
    }
    if (std::filesystem::exists(projectManager->projectDir))
    {
        RL_LOG_ERROR("Project with the same name already exists.");
        return false;
    }

    std::filesystem::create_directory(projectManager->projectDir);
    if (!std::filesystem::exists(projectManager->projectDir))
    {
        RL_LOG_ERROR("Unable to create project Directory.");
        return false;
    }

    if (!std::filesystem::exists(projectManager->projectDir + "/Assets"))
    {
        std::filesystem::create_directory(projectManager->projectDir + "/Assets");
    }

    if (!std::filesystem::exists(projectManager->projectDir + "/ProjectData"))
    {
        std::filesystem::create_directory(projectManager->projectDir + "/ProjectData");
    }

    projectManager->projectOpen = true;
    AssetBrowser::Setup(projectManager->projectDir);
    return true;
}

bool ProjectManager::Open(const std::string& name, const std::string& path)
{
    projectManager->projectName = name;
    projectManager->projectDir = path + "/" + name + "/";

    if (name.empty() || path.empty())
    {
        RL_LOG_ERROR("Name or Path not entered.");
        return false;
    }
    if (!std::filesystem::exists(projectManager->projectDir))
    {
        RL_LOG_ERROR("The project you are trying to open doesnt exist.");
        return false;
    }

    if (!std::filesystem::exists(projectManager->projectDir + "/ProjectData"))
    {
        RL_LOG_ERROR("The project you are trying to open is corrupt.");
        return false;
    }
    if (!std::filesystem::exists(projectManager->projectDir + "/Assets"))
    {
        RL_LOG_ERROR("The project you are trying to open is corrupt.");
        return false;
    }

    projectManager->projectOpen = true;
    AssetBrowser::Setup(projectManager->projectDir);
    return true;
}

void ProjectManager::Compile()
{
    if (!projectManager->projectOpen)
    {
        RL_LOG_ERROR("No Project Open.");
        return;
    }

    std::filesystem::remove_all(projectManager->projectDir + "/ProjectData/temp");
    std::filesystem::create_directory("./logs/");

    Application::GetLogger().ClearMessages();
    Console::ClearBuildLogs();
    CodeManager::Generate();

    // split
    projectManager->threadVal = std::async(&CompileInternal, projectManager->projectDir);
    projectManager->threadExists = true;
}

void ProjectManager::Update()
{
    if (!projectManager->threadExists)
        return;

    Console::UpdateBuildLogs();

    if (projectManager->threadVal.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
        return;

    projectManager->threadExists = false;
    bool result = projectManager->threadVal.get();

    Editor::Pause();
    Application::Reset();

    if (!result)
    {
        RL_LOG_ERROR("Error while Compiling: ");
        return;
    }
    RL_LOG_WARNING("Game Context Compiled.");

    if (!std::filesystem::exists(projectManager->projectDir + "/ProjectData/out/Game.dll"))
    {
        RL_LOG_ERROR("Cannot find Game Context(dynamic library).");
        return;
    }

    Application::SetGameContext(nullptr);

    std::filesystem::remove("./Game.dll");
    std::filesystem::copy_file(projectManager->projectDir + "/ProjectData/out/Game.dll", "./Game.dll",
                               std::filesystem::copy_options::overwrite_existing);

    Application::SetGameContext(DynamicLibrary::Load(std::filesystem::path("Game.dll")));

    Start();
    RL_LOG_WARNING("Game Context Setup.");
}

bool ProjectManager::CompileInternal(const std::string& projectDir)
{
    int debugLevel = 0;
#ifdef _ITERATOR_DEBUG_LEVEL
    debugLevel = _ITERATOR_DEBUG_LEVEL;
#endif

    std::string command = "cmake -S " + projectDir + " -B " + projectDir + "/ProjectData/temp"
                          + " -DEDITOR_PATH:STRING=" + std::filesystem::current_path().string()
                          + " -DRL_BUILD_FLAGS:STRING=\"" + RL_BUILD_FLAGS + "\"" + " -DRL_BUILD_CONFIG_FLAGS:STRING=\""
                          + (debugLevel == 0 ? "" : "/MDd ") + RL_BUILD_CONFIG_FLAGS + "\""
                          + " -DRL_DEBUG_LEVEL=" + std::to_string(debugLevel) + " > ./logs/CMakeOut.txt";
    system(command.c_str());

    command = "cmake --build " + projectDir + "/ProjectData/temp" + " > ./logs/BuildOut.txt";
    int code = system(command.c_str());
    return code == 0;
}

bool ProjectManager::IsProjectOpen()
{
    return projectManager->projectOpen;
}

bool ProjectManager::IsProjectCompiled()
{
    return Application::GetGameContext() != nullptr;
}

std::string ProjectManager::GetProjectDirectory()
{
    return projectManager->projectDir;
}

void ProjectManager::Start()
{
    if (!Application::GetGameContext())
    {
        RL_LOG_ERROR("Game Context(dynamic lib) not loaded");
        return;
    }

    Application::GetGameContext()->RunFunctionVal<void>("GameSetup", (void*)Application::GetSharedPtr());
}
