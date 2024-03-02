#include "Application.h"
#include "Input.h"

#include "../ecs/SystemManager.h"

#include "../components/Transform.h"
#include "../components/MeshComponent.h"

using namespace rl;

void Application::Run() {

    // create window
    const auto window = Window::Create(1280, 720, "RL Engine 2.0", false);
    window->setResizeCallback(OnWindowResize);

    // setup renderer
    Renderer::Start(window);
    System renderSystem;
    renderSystem.Update = Renderer::Render;

    SystemManager::AddSystem(renderSystem);

    // create test entity
    Entity test = 0;
    Transform::Create(test);
    MeshComponent::Create(test);
    MeshComponent::GetComponent(test)->LoadMesh("test.obj");

    // create camera entity
    Entity cam = 1;
    Transform::Create(cam);
    //Camera::Create(test);

    // run window
    SystemManager::StartSystems();
    while (window->Update()){
        SystemManager::UpdateSystems();
    }
}

void Application::OnWindowResize(Window* window, int width, int height){
    Renderer::Resize(width, height);
}