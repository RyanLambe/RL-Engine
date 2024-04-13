#include "Application.h"

#include "../graphics/Renderer.h"
#include "../ecs/SystemManager.h"

using namespace rl;

Application::Application() {
    // create window
    window = Window::Create(1280, 720, "RL Engine 2.0", false);
    window->setResizeCallback(OnWindowResize);

    // setup renderer
    renderer = std::make_unique<Renderer>(window);
}

void Application::Run() {

    SystemManager::StartSystems();
    while (window->Update()){
        SystemManager::UpdateSystems();
    }
}

void Application::OnWindowResize(Window* window, int width, int height){
    //Renderer::Resize(width, height);
}
