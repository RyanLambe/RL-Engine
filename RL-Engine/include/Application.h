#pragma once
#include <msclr\marshal_cppstd.h>

#ifndef INCLUDE
#define INCLUDE
#include "../../RL-EngineCore/include/Window.h"
#endif

#include "objects/Script.h"

namespace Engine {
    public ref class Application {
    public:
        Application(System::String^ name, int width, int height, bool debugMode);
        ~Application();
        !Application();

        int Run(array<Script^>^ scripts);
        static void Close();
        static void SetFullscreen(bool fullscreen);

    private:
        bool WindowClosed(Core::Window::ExitCode exitCode);
        int exitCode = -1;
        static bool close;

        Core::Window* instance;
    };
}
