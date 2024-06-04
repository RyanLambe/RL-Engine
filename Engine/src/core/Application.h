#pragma once

#include "Window.h"
#include "../graphics/Renderer.h"
#include "../ecs/SystemManager.h"
#include "../ecs/SceneManager.h"
#include "../components/Camera.h"

namespace rl {
    class Application {
    public:
        Application();

        static Application& GetApplication();
        static std::shared_ptr<Application>* GetSharedPtr();
        static void ConnectToApp(std::shared_ptr<Application>* mainApp);

        static void Setup(int width, int height, const std::string& title, bool fullscreen = false, RLWindowResizeCallback callback = nullptr);
        void Run();

        static bool IsSetup();

        static Window& GetWindow();
        static Renderer& GetRenderer();
        static SystemManager& GetSystemManager();
        static Scene& GetScene();

        static Window* GetWindowUnsafe();
        static Camera* GetMainCamera();

        static void SetMainCamera(Camera* cam);

    private:
        static std::shared_ptr<Application> app;
        bool isSetup = false;

        std::shared_ptr<Window> window = nullptr;
        std::unique_ptr<Renderer> renderer = nullptr;

        std::unique_ptr<Scene> scene = nullptr;
        Camera* mainCamera = nullptr;

        std::unique_ptr<SystemManager> systemManager = nullptr; // todo: move to Scene?
    };
}
