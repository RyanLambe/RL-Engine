#ifndef Eng_ManagedWindow
#define Eng_ManagedWindow
#include "../pch.h"

#include "types/Managed.h"

namespace Engine {
    public ref class ManagedWindow : public Engine::Managed<Core::Window> {
    public:

        ManagedWindow(HINSTANCE hInstance, LPCWSTR name, DWORD style, int width, int height);

        int Run(void (*UpdateFunc)(void));
    };
}

#endif
