#include "CodeManager.h"

#include "../project/ProjectManager.h"
#include "core/Logger.h"
#include "fstream"

namespace rl::ed
{
    std::vector<std::string> CodeManager::systems = {};
    std::vector<std::string> CodeManager::components = {};

    std::unordered_map<std::string, std::string> CodeManager::cppFiles = {};
    std::unordered_map<std::string, std::string> CodeManager::headerFiles = {};

    void CodeManager::AddSystem(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile)
    {
        if (cppFile.stem() != headerFile.stem())
        {
            RL_LOG_ERROR("Cpp files and Header files must have the same name.");
            return;
        }

        if (cppFiles.contains(cppFile.stem().string()) || headerFiles.contains(headerFile.stem().string()))
        {
            RL_LOG_ERROR("The cpp file: ", cppFile.stem(), " already exists.");
            return;
        }

        systems.push_back(cppFile.stem().string());
        cppFiles[cppFile.stem().string()] = cppFile.string();
        headerFiles[headerFile.stem().string()] = headerFile.string();
    }

    void CodeManager::AddComponent(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile)
    {
        if (cppFile.stem() != headerFile.stem())
        {
            RL_LOG_ERROR("Cpp files and Header files must have the same name.");
            return;
        }

        if (cppFiles.contains(cppFile.stem().string()) || headerFiles.contains(headerFile.stem().string()))
        {
            RL_LOG_ERROR("The cpp file: ", cppFile.stem(), " already exists.");
            return;
        }

        components.push_back(cppFile.stem().string());
        cppFiles[cppFile.stem().string()] = cppFile.string();
        headerFiles[headerFile.stem().string()] = headerFile.string();
    }

    void CodeManager::Generate()
    {
        GenerateCmake();
        GenerateSetupCpp();
    }

    void CodeManager::GenerateCmake()
    {
        std::ofstream file(ProjectManager::GetProjectDirectory() + "/CMakeLists.txt");

        file << "cmake_minimum_required(VERSION 3.5)\n"
             << "project(Game)\n\n"
             << "message(\"EDITOR_PATH: ${EDITOR_PATH}\")\n"
             << "message(\"RL_BUILD_FLAGS: ${RL_BUILD_FLAGS}\")\n"
             << "message(\"RL_BUILD_CONFIG_FLAGS: ${RL_BUILD_CONFIG_FLAGS}\")\n"
             << "message(\"RL_DEBUG_LEVEL: ${RL_DEBUG_LEVEL}\")\n\n"
             << "set(CMAKE_CXX_FLAGS_RELEASE ${RL_BUILD_CONFIG_FLAGS})\n"
             << "set(CMAKE_CXX_FLAGS_DEBUG ${RL_BUILD_CONFIG_FLAGS})\n"
             << "set(CMAKE_CXX_FLAGS ${RL_BUILD_FLAGS})\n\n"
             << "set(CMAKE_CXX_STANDARD 20)\n"
             << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/ProjectData/out)\n"
             << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/ProjectData/out)\n"
             << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/ProjectData/out)\n\n"
             << "find_library(GLFW NAMES glfw3 PATHS ${EDITOR_PATH})\n"
             << "find_library(ENGINE NAMES Engine PATHS ${EDITOR_PATH})\n\n"
             << "add_library(Game SHARED ProjectData/Setup.cpp ProjectData/Setup.h\n"
             << "\t# .cpp files within project\n";

        for (const auto& cppFile : cppFiles)
        {
            file << cppFile.second << "\n";
        }

        file << "\n\t# .h files within project\n";

        for (const auto& hFile : headerFiles)
        {
            file << hFile.second << "\n";
        }

        file << ")\n\n"
             << "target_include_directories(Game PUBLIC ${EDITOR_PATH}/include)\n"
             << "target_include_directories(Game PUBLIC ${EDITOR_PATH}/ThirdParty/glm)\n"
             << "target_include_directories(Game PUBLIC ${EDITOR_PATH}/ThirdParty/glfw)\n"
             << "target_link_libraries(Game PRIVATE ${GLFW})\n"
             << "target_link_libraries(Game PRIVATE ${ENGINE})\n\n"
             << "target_compile_definitions(Game PUBLIC _ITERATOR_DEBUG_LEVEL=${RL_DEBUG_LEVEL})\n";

        file.close();
    }

    void CodeManager::GenerateSetupCpp()
    {
        std::ofstream file(ProjectManager::GetProjectDirectory() + "/ProjectData/Setup.cpp");

        file << "#include \"Setup.h\"\n"
             << "#include \"Engine.h\"\n\n";

        for (const auto& hFile : headerFiles)
        {
            file << "#include \"../" << hFile.second << "\"\n";
        }

        file << "\nusing namespace rl;\n\n"
             << "void GameSetupInternal(void* mainApp);\n\n"
             << "extern \"C\" void GameSetup(void* mainApp) {\n"
             << "\tGameSetupInternal(mainApp);\n"
             << "}\n\n"
             << "void GameSetupInternal(void* mainApp){\n"
                "\tApplication::ConnectToApp((std::shared_ptr<Application>*)mainApp);\n\n";

        // todo: find better way to add systems that is linked to the scene
        file << "\tApplication::GetScene().systemManager.AddSystem<Renderer>();\n";
        for (const auto& system : systems)
        {
            file << "\tApplication::GetScene().systemManager.AddSystem<" << system << ">();\n";
        }
        file << "}\n";

        file.close();
    }
}