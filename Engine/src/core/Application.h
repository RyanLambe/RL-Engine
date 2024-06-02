#pragma once

#include "Window.h"
#include "../graphics/Renderer.h"
#include "../ecs/SystemManager.h"

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

        static Window* GetWindowUnsafe();

    private:
        static std::shared_ptr<Application> app;
        bool isSetup = false;

        std::shared_ptr<Window> window = nullptr;
        std::unique_ptr<Renderer> renderer = nullptr;
        std::unique_ptr<SystemManager> systemManager = nullptr;
    };
}
