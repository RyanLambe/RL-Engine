#pragma once

#include "Window.h"
#include "../graphics/Renderer.h"

namespace rl {
    class Application {
    public:
        void Run();

    private:
        static void OnWindowResize(Window* window, int width, int height);

        static std::unique_ptr<Renderer> renderer;

    };
}
