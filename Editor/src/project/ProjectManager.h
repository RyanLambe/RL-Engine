#pragma once

#include <windows.h>

#include <string>

namespace rl::editor
{

    class ProjectManager
    {
    public:
        ProjectManager();
        ~ProjectManager();

        static bool New(const std::string& name, const std::string& path);
        static bool Open(const std::string& name, const std::string& path);
        static void Compile();

        static void Run();

    private:
        static ProjectManager* projectManager;

        bool projectOpen = false;
        std::string projectName;
        std::string projectDir;
        HINSTANCE library = nullptr;
    };

}