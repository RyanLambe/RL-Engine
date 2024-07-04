#pragma once

#include "../components/Camera.h"
#include "../ecs/SceneManager.h"
#include "../ecs/SystemManager.h"
#include "../graphics/GraphicsContext.h"
#include "Logger.h"
#include "Window.h"

namespace rl
{
    class Application
    {
    public:
        Application();

        static Application& GetApplication();
        static std::shared_ptr<Application>* GetSharedPtr();
        static void ConnectToApp(std::shared_ptr<Application>* mainApp);

        static void Setup(int width, int height, const std::string& title, bool fullscreen = false,
                          RLWindowResizeCallback callback = nullptr);
        static void Update();
        static void Reset();

        static bool IsSetup();

        static Scene& GetScene();

        static Logger& GetLogger();

        static Window& GetWindow();
        static Window* GetWindowUnsafe();
        static std::weak_ptr<Window> GetWindowPtr();

        static GraphicsContext* GetGraphicsContextUnsafe();
        static std::weak_ptr<GraphicsContext> GetGraphicsContextPtr();

    private:
        static std::shared_ptr<Application> app;
        static bool allowApplicationCreation;
        bool isSetup = false;

        std::unique_ptr<Scene> scene = nullptr;
        std::unique_ptr<Logger> logger = nullptr;
        std::shared_ptr<Window> window = nullptr;
        std::shared_ptr<GraphicsContext> graphicsContext = nullptr;
    };
}
