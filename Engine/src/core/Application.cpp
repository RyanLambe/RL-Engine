#include "Application.h"
#include "Input.h"

#include "../ecs/SystemManager.h"

#include "../components/Transform.h"
#include "../components/MeshComponent.h"
#include "../components/Camera.h"

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
    MeshComponent::GetComponent(test).LoadMesh("test.obj");

    // create camera entity
    Entity cam = 1;
    Transform::Create(cam);
    Camera::Create(cam).SetMain();

    glm::vec3 pos = glm::vec3(0, 0, -5);
    glm::vec3 rot = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);

    // run window
    SystemManager::StartSystems();
    while (window->Update()){
        SystemManager::UpdateSystems();

        if(Input::GetKey(Key::W)){
            pos.z += 0.001f;
        }
        if(Input::GetKey(Key::S)){
            pos.z -= 0.001f;
        }

        if(Input::GetKey(Key::A)){
            pos.x -= 0.001f;
        }
        if(Input::GetKey(Key::D)){
            pos.x += 0.001f;
        }

        if (Input::GetKey(Key::E)) {
            pos.y += 0.001f;
        }
        if (Input::GetKey(Key::Q)) {
            pos.y -= 0.001f;
        }

        if (Input::GetKey(Key::I)) {
            rot.x += 0.01f;
        }
        if (Input::GetKey(Key::K)) {
            rot.x -= 0.01f;
        }

        if (Input::GetKey(Key::J)) {
            rot.y += 0.01f;
        }
        if (Input::GetKey(Key::L)) {
            rot.y -= 0.01f;
        }

        if (Input::GetKey(Key::O)) {
            rot.z += 0.01f;
        }
        if (Input::GetKey(Key::U)) {
            rot.z -= 0.01f;
        }

        if (Input::GetKey(Key::N)) {
            scale -= 0.0001f;
        }
        if (Input::GetKey(Key::M)) {
            scale += 0.0001f;
        }

        Transform::GetComponent(cam).position = pos;
        Transform::GetComponent(cam).rotation = rot;
        Transform::GetComponent(test).scale = scale;
    }
}

void Application::OnWindowResize(Window* window, int width, int height){
    Renderer::Resize(width, height);
}