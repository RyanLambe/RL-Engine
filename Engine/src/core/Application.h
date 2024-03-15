#pragma once

#include "Window.h"

namespace rl {
    class Application {
    public:
        Application();
        void Run();

    private:
        static void OnWindowResize(Window* window, int width, int height);

        std::shared_ptr<Window> window = nullptr;
    };
}
