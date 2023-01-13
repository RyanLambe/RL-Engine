#pragma once
#include <msclr\marshal_cppstd.h>

#ifndef INCLUDE
#define INCLUDE
#include "../../RL-EngineCore/include/Window.h"
#endif

#include "types/Managed.h"
#include "objects/Script.h"

namespace Engine {
    public ref class ManagedWindow : public Managed<Core::Window> {
    public:
        ManagedWindow(System::String^ name, int width, int height);
        int Run(array<Script^>^ scripts);
        static void Close();
        static void SetFullscreen(bool fullscreen);

    private:
        bool WindowClosed(Core::Window::ExitCode exitCode);
        int exitCode = -1;
        static bool close;
    };
}
