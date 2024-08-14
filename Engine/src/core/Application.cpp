#include "Application.h"

#include "../ecs/SystemManager.h"
#include "RLResult.h"

namespace rl
{
    std::shared_ptr<Application> Application::app = nullptr;
    bool Application::allowApplicationCreation = false;

    // don't allow application to be constructed unless allowApplicationCreation set
    // to true
    Application::Application()
    {
        if (!allowApplicationCreation)
        {
            RL_THROW_EXCEPTION("Application is a singleton, use GetApplication() to "
                               "access the singleton.");
        }
    }

    // create app if it doesn't exist, get app
    Application& Application::GetApplication()
    {
        if (app == nullptr)
        {
            allowApplicationCreation = true;
            app = std::make_shared<Application>();
            allowApplicationCreation = false;
        }
        return *app;
    }

    std::shared_ptr<Application>* Application::GetSharedPtr()
    {
        return &app;
    }

    void Application::ConnectToApp(std::shared_ptr<Application>* mainApp)
    {
        app = *mainApp;
        app->window->EnableContext();
    }

    void Application::Setup(int width, int height, const std::string& title, bool fullscreen,
                            RLWindowResizeCallback callback)
    {
        if (app == nullptr)
        {
            GetApplication(); // creates app, can ignore result since it's saved in app
        }

        // create window
        app->window = Window::Create(width, height, title, fullscreen);
        app->window->SetResizeCallback(callback);

        // create graphics context
        app->graphicsContext = GraphicsContext::Create(app->window.get());

        // setup scene
        app->sceneManager = std::make_unique<SceneManager>();

        // setup logger
        app->logger = std::make_unique<Logger>();

        app->isSetup = true;
    }

    void Application::Update()
    {
        app->sceneManager->GetCurrentScene().systemManager.UpdateSystems();
    }

    void Application::Reset()
    {
        app->logger->ClearMessages();
        if(app->sceneManager->IsSceneOpen())
            app->sceneManager->GetCurrentScene().Reset();
    }

    bool Application::IsSetup()
    {
        return app->isSetup;
    }

    Window& Application::GetWindow()
    {
        return *app->window;
    }

    Window* Application::GetWindowUnsafe()
    {
        return app->window.get();
    }

    std::weak_ptr<Window> Application::GetWindowPtr()
    {
        return app->window;
    }

    SceneManager& Application::GetSceneManager()
    {
        return *app->sceneManager;
    }

    Logger& Application::GetLogger()
    {
        return *app->logger;
    }

    std::weak_ptr<GraphicsContext> Application::GetGraphicsContextPtr()
    {
        return app->graphicsContext;
    }

    GraphicsContext* Application::GetGraphicsContextUnsafe()
    {
        return app->graphicsContext.get();
    }

    bool Application::isGameContextCreated()
    {
        return app->gameContext != nullptr;
    }

    GameContext& Application::GetGameContext()
    {
        return *app->gameContext;
    }

    void Application::CreateNewGameContext(const std::shared_ptr<DynamicLibrary>& newLib)
    {
        app->gameContext = std::make_unique<GameContext>(newLib);
    }

    void Application::RemoveGameContext()
    {
        app->gameContext = nullptr;
    }
}
