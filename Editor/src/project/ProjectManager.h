#pragma once

#include <windows.h>
#include <thread>
#include <string>
#include <future>
#include <optional>

namespace rl::editor
{

    class ProjectManager
    {
    public:
        ProjectManager();
        ~ProjectManager();

        static bool New(const std::string& name, const std::string& path);
        static bool Open(const std::string& name, const std::string& path);

        static void Start();

        static void Compile();
        static void Update();

    private:
        static ProjectManager* projectManager;

        bool projectOpen = false;
        std::string projectName;
        std::string projectDir;
        HINSTANCE library = nullptr;

        static bool CompileInternal(const std::string& projectDir);

        bool threadExists = false;
        std::future<bool> threadVal;
    };

}