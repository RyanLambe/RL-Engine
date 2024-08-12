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

        static bool New(const std::string& name, const std::string& path);
        static bool Open(const std::string& name, const std::string& path);

        static void Compile();
        static void Update();

        static bool IsProjectOpen();
        static bool IsProjectCompiled();
        static std::string GetProjectDirectory();

    private:
        static ProjectManager* projectManager;

        bool projectOpen = false;
        std::string projectName;
        std::string projectDir;

        static bool CompileInternal(const std::string& projectDir);
        static void Start();

        bool threadExists = false;
        std::future<bool> threadVal;
    };

}