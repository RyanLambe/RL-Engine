#pragma once

#include <future>
#include <optional>
#include <string>
#include <thread>

#include "core/Logger.h"
#include "core/Application.h"

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

        template<typename T, typename... Args> static T RunFunction(const std::string& name, const Args&... args)
        {
            if (!Application::GetGameContext())
            {
                RL_LOG_ERROR("Game Context(dynamic lib) not loaded");
                return T();
            }
            return Application::GetGameContext()->RunFunction<T>(name, args...);
        }

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