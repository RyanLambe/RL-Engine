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

    // create test entities
    Entity test = 0;
    Transform::Create(test);
    MeshComponent::Create(test);
    MeshComponent::GetComponent(test).LoadMesh("test.obj");
    Transform::GetComponent(test).position = glm::vec3(0, 0, -5);

    Entity test1 = 2;
    Transform::Create(test1);
    MeshComponent::Create(test1);
    MeshComponent::GetComponent(test1).LoadMesh("test.obj");
    Transform::GetComponent(test1).position = glm::vec3(0, 0, 5);

    Entity test2 = 3;
    Transform::Create(test2);
    MeshComponent::Create(test2);
    MeshComponent::GetComponent(test2).LoadMesh("test.obj");
    Transform::GetComponent(test2).position = glm::vec3(-5, 0, 0);

    Entity test3 = 4;
    Transform::Create(test3);
    MeshComponent::Create(test3);
    MeshComponent::GetComponent(test3).LoadMesh("test.obj");
    Transform::GetComponent(test3).position = glm::vec3(5, 0, 0);

    Entity test4 = 5;
    Transform::Create(test4);
    MeshComponent::Create(test4);
    MeshComponent::GetComponent(test4).LoadMesh("test.obj");
    Transform::GetComponent(test4).position = glm::vec3(0, -5, 0);

    Entity test5 = 6;
    Transform::Create(test5);
    MeshComponent::Create(test5);
    MeshComponent::GetComponent(test5).LoadMesh("test.obj");
    Transform::GetComponent(test5).position = glm::vec3(0, 5, 0);

    // create camera entity
    Entity cam = 1;
    Transform::Create(cam);
    Camera::Create(cam).SetMain();

    // run window
    SystemManager::StartSystems();
    while (window->Update()){
        SystemManager::UpdateSystems();

        if(Input::GetKey(Key::W)){
            Transform::GetComponent(cam).Translate(0, 0, 0.01f);
        }
        if(Input::GetKey(Key::S)){
            Transform::GetComponent(cam).Translate(0, 0, -0.01f);
        }

        if(Input::GetKey(Key::A)){
            Transform::GetComponent(cam).Translate(-0.01f, 0, 0);
        }
        if(Input::GetKey(Key::D)){
            Transform::GetComponent(cam).Translate(0.01f, 0, 0);
        }

        if (Input::GetKey(Key::E)) {
            Transform::GetComponent(cam).Translate(0, 0.01f, 0);
        }
        if (Input::GetKey(Key::Q)) {
            Transform::GetComponent(cam).Translate(0, -0.01f, 0);
        }

        if (Input::GetKey(Key::I)) {
            Transform::GetComponent(cam).Rotate(-0.1f, 0, 0);
            //rot.x -= 0.1f;
        }
        if (Input::GetKey(Key::K)) {
            Transform::GetComponent(cam).Rotate(0.1f, 0, 0);
            //rot.x += 0.1f;
        }

        if (Input::GetKey(Key::J)) {
            Transform::GetComponent(cam).Rotate(0, -0.1f, 0);
        }
        if (Input::GetKey(Key::L)) {
            Transform::GetComponent(cam).Rotate(0, 0.1f, 0);
        }

        if (Input::GetKey(Key::O)) {
            Transform::GetComponent(cam).Rotate(0, 0, -0.1f);
        }
        if (Input::GetKey(Key::U)) {
            Transform::GetComponent(cam).Rotate(0, 0, 0.1f);
        }

        if (Input::GetKey(Key::N)) {
            Transform::GetComponent(test1).Scale(0.9999f);
        }
        if (Input::GetKey(Key::M)) {
            Transform::GetComponent(test1).Scale(1.0001f);
        }

        glm::vec3 rot = Transform::GetComponent(cam).EulerAngles();
        RL_LOG(rot.x, ", ", rot.y, ", ", rot.z);
    }
}

void Application::OnWindowResize(Window* window, int width, int height){
    Renderer::Resize(width, height);
}