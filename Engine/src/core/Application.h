#pragma once

#include "Window.h"
#include "../ecs/SystemManager.h"
#include "../ecs/SceneManager.h"
#include "../components/Camera.h"
#include "../graphics/GraphicsContext.h"

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
        static Window* GetWindowUnsafe();
        static std::weak_ptr<Window> GetWindowPtr();

        static Scene& GetScene();

        static GraphicsContext* GetGraphicsContextUnsafe();
        static std::weak_ptr<GraphicsContext> GetGraphicsContextPtr();

    private:
        static std::shared_ptr<Application> app;
        bool isSetup = false;

        std::shared_ptr<Window> window = nullptr;
        std::unique_ptr<Scene> scene = nullptr;
        std::shared_ptr<GraphicsContext> graphicsContext = nullptr;
    };
}
