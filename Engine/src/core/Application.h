#pragma once

#include "Window.h"
#include "../graphics/Renderer.h"

namespace rl {
    class Application {
    public:
        Application();
        void Run();

    private:
        static void OnWindowResize(Window* window, int width, int height);

        std::shared_ptr<Window> window = nullptr;
        std::unique_ptr<Renderer> renderer = nullptr;
    };
}
