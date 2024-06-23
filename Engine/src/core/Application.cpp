#include "Application.h"

#include "../ecs/SystemManager.h"
#include "RLResult.h"

using namespace rl;

std::shared_ptr<Application> Application::app = nullptr;

// don't allow application to be constructed unless allowApplicationCreation set to true
bool allowApplicationCreation = false;
Application::Application() {
    if(!allowApplicationCreation){
        RL_THROW_EXCEPTION("Application is a singleton, use GetApplication() to access the singleton.");
    }
}

// create app if it doesn't exist, get app
Application &Application::GetApplication() {
    if(app == nullptr){
        allowApplicationCreation = true;
        app = std::make_shared<Application>();
        allowApplicationCreation = false;
    }
    return *app;
}

std::shared_ptr<Application>* Application::GetSharedPtr() {
    return &app;
}

void Application::ConnectToApp(std::shared_ptr<Application>* mainApp) {
    app = *mainApp;
}

void Application::Setup(int width, int height, const std::string& title, bool fullscreen, RLWindowResizeCallback callback) {
    if (app == nullptr){
        GetApplication(); // creates app, can ignore result since it's saved in app
    }

    // create window
    app->window = Window::Create(width, height, title, fullscreen);
    app->window->setResizeCallback(callback);

    // setup renderer
    app->renderer = std::make_unique<Renderer>(app->window);

    // setup scene
    app->scene = std::make_unique<Scene>();

    app->isSetup = true;
}

bool Application::IsSetup() {
    return app->isSetup;
}

Window &Application::GetWindow() {
    return *app->window;
}

Renderer &Application::GetRenderer() {
    return *app->renderer;
}

Scene &Application::GetScene() {
    return *app->scene;
}

Window *Application::GetWindowUnsafe() {
    return app->window.get();
}
