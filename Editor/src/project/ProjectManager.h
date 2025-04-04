#pragma once

#include <future>
#include <optional>
#include <string>
#include <thread>

#include "core/Application.h"
#include "core/Logger.h"

namespace rl::ed
{
    class ProjectManager
    {
    public:
        ProjectManager();
        ~ProjectManager();

        static void SetProjectsFolder(const std::filesystem::path& projectsFolder);
        static void RefreshProjectsFolder();

        static const std::vector<std::filesystem::path>& GetProjects();

        static bool New(const std::string& name);
        static bool Open(const std::filesystem::path& project);

        static void Compile();
        static void Update();

        static bool IsProjectOpen();
        static bool IsProjectCompiled();
        static std::string GetProjectDirectory();

    private:
        static ProjectManager* projectManager;

        static std::filesystem::path rootFolder;
        static std::vector<std::filesystem::path> projects;

        bool projectOpen = false;
        std::string projectName;
        std::filesystem::path projectDir;

        static bool CompileInternal(const std::string& projectDir);
        static void Start();

        bool threadExists = false;
        std::future<bool> threadVal;
    };

}