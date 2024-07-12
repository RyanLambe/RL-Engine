#include <Engine.h>

#include <iostream>

using namespace rl;

const Entity test = 0;

const Entity test1 = 2;
const Entity test2 = 3;
const Entity test3 = 4;
const Entity test4 = 5;
const Entity test5 = 6;
const Entity cam = 1;

class Demo : public System
{
public:
    //std::shared_ptr<Mesh> monkeyHead = nullptr;

    void Start() override
    {
        // load mesh to memory
        /*monkeyHead = static_pointer_cast<Mesh>(Asset::ImportAsset(std::filesystem::path("test.obj")));

        // create test entities
        Transform::Create(test);
        MeshComponent::Create(test);
        MeshComponent::GetComponent(test).LoadMesh(monkeyHead);
        Transform::GetComponent(test).position = glm::vec3(0, 0, -5);

        Transform::Create(test1);
        MeshComponent::Create(test1);
        MeshComponent::GetComponent(test1).LoadMesh(monkeyHead);
        Transform::GetComponent(test1).position = glm::vec3(0, 0, 5);

        Transform::Create(test2);
        MeshComponent::Create(test2);
        MeshComponent::GetComponent(test2).LoadMesh(monkeyHead);
        Transform::GetComponent(test2).position = glm::vec3(-5, 0, 0);

        Transform::Create(test3);
        MeshComponent::Create(test3);
        MeshComponent::GetComponent(test3).LoadMesh(monkeyHead);
        Transform::GetComponent(test3).position = glm::vec3(5, 0, 0);

        Transform::Create(test4);
        MeshComponent::Create(test4);
        MeshComponent::GetComponent(test4).LoadMesh(monkeyHead);
        Transform::GetComponent(test4).position = glm::vec3(0, -5, 0);

        Transform::Create(test5);
        MeshComponent::Create(test5);
        MeshComponent::GetComponent(test5).LoadMesh(monkeyHead);
        Transform::GetComponent(test5).position = glm::vec3(0, 5, 0);*/

        // create camera entity
        Transform::Create(cam);
        Camera::Create(cam).SetMain();
        Camera::GetComponent(cam).RenderToWindow();
    }

    void Update() override
    {
        if (Input::GetKey(Key::Keyboard::W) > 0)
        {
            Transform::GetComponent(cam).Translate(0, 0, 0.01f);
        }
        if (Input::GetKey(Key::Keyboard::S) > 0)
        {
            Transform::GetComponent(cam).Translate(0, 0, -0.01f);
        }
        if (Input::GetKey(Key::Keyboard::A) > 0)
        {
            Transform::GetComponent(cam).Translate(-0.01f, 0, 0);
        }
        if (Input::GetKey(Key::Keyboard::D) > 0)
        {
            Transform::GetComponent(cam).Translate(0.01f, 0, 0);
        }
        if (Input::GetKey(Key::Keyboard::E) > 0)
        {
            Transform::GetComponent(cam).Translate(0, 0.01f, 0);
        }
        if (Input::GetKey(Key::Keyboard::Q) > 0)
        {
            Transform::GetComponent(cam).Translate(0, -0.01f, 0);
        }
        if (Input::GetKey(Key::Keyboard::I) > 0)
        {
            Transform::GetComponent(cam).Rotate(-0.1f, 0, 0);
        }
        if (Input::GetKey(Key::Keyboard::K) > 0)
        {
            Transform::GetComponent(cam).Rotate(0.1f, 0, 0);
        }
        if (Input::GetKey(Key::Keyboard::J) > 0)
        {
            Transform::GetComponent(cam).Rotate(0, -0.1f, 0);
        }
        if (Input::GetKey(Key::Keyboard::L) > 0)
        {
            Transform::GetComponent(cam).Rotate(0, 0.1f, 0);
        }
        if (Input::GetKey(Key::Keyboard::O) > 0)
        {
            Transform::GetComponent(cam).Rotate(0, 0, -0.1f);
        }
        if (Input::GetKey(Key::Keyboard::U) > 0)
        {
            Transform::GetComponent(cam).Rotate(0, 0, 0.1f);
        }

        /*if (Input::GetKey(Key::Keyboard::N) > 0)
        {
            Transform::GetComponent(test1).Scale(0.9999f);
        }
        if (Input::GetKey(Key::Keyboard::M) > 0)
        {
            Transform::GetComponent(test1).Scale(1.0001f);
        }*/

        Transform temp = Transform::GetComponent(cam);
        glm::vec3 rot = Transform::GetComponent(cam).GetPosition();
        //RL_LOG(rot.x, ", ", rot.y, ", ", rot.z);
    }
};

int main()
{
    Application::Setup(1280, 720, "RL Engine 2.0", false);

    Application::GetScene().systemManager.AddSystem<Demo>();

    // Application::GetRenderer().RenderToWindow();

    Application::GetScene().systemManager.StartSystems();
    while (Application::GetWindow().Update())
    {
        Application::Update();
        Application::GetGraphicsContextUnsafe()->Present();

        for (const auto& message : Application::GetLogger().GetMessages())
        {
            std::cout << message.GetFormatted() << '\n';
        }
        Application::GetLogger().ClearMessages();
    }
}