#include "Application.h"

using namespace rl;

std::unique_ptr<Renderer> Application::renderer;

void Application::Run() {

    // create window
    auto window = Window::Create(1280, 720, "RL Engine 2.0", false);
    window->setResizeCallback(OnWindowResize);

    renderer = std::make_unique<Renderer>(window);

    // run window
    while (window->Update()){
        renderer->Render();
    }
}

void Application::OnWindowResize(Window* window, int width, int height){
    renderer->Resize(width, height);
}