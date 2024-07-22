#pragma once

#include <windows.h>

#include <future>
#include <optional>
#include <string>
#include <thread>
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
        static std::string GetProjectDirectory();

        template<typename T, typename... Args>
        static T RunFunction(const std::string& name, const Args&... args){
            if (!projectManager->library)
            {
                RL_LOG_ERROR("Game.dll not loaded");
                return T();
            }

            typedef T (*FuncType)(const Args&... args);
            auto func = (FuncType)GetProcAddress(projectManager->library, name.c_str());
            if (!func)
            {
                RL_LOG_ERROR(name, " function not found: ", GetLastError());
                return T();
            }

            try
            {
                return func(args...);
            }
            catch (...)
            {
                RL_LOG_ERROR("THSI IASDJFKLASJDF");
                // do nothing? todo: should probably recompile after code fixes are made
            }
            return T();
        }

    private:
        static ProjectManager* projectManager;

        bool projectOpen = false;
        std::string projectName;
        std::string projectDir;
        HINSTANCE library = nullptr;

        static bool CompileInternal(const std::string& projectDir);
        static void Start();

        bool threadExists = false;
        std::future<bool> threadVal;
    };

}