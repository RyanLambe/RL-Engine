#include "glfwWindow.h"

#include <GLFW/glfw3native.h>

#include "../../core/Application.h"
#include "../../core/RLResult.h"

using namespace rl;

glfwWindow::glfwWindow(int width, int height, const std::string& title, bool fullscreen)
{
    if (!glfwInit())
    {
        RL_THROW_EXCEPTION("Failed to initialize glfw.");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);

    GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
    if (!window)
    {
        glfwTerminate();
        RL_THROW_EXCEPTION("Failed to create glfw window.");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, internalResizeCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    minWidth = width;
    minHeight = height;
    if (fullscreen)
    {
        maxWidth = width;
        maxHeight = height;
    }
    else
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        maxWidth = mode->width;
        maxHeight = mode->height;
    }

    isFullscreen = fullscreen;
}

glfwWindow::~glfwWindow()
{
    if (RLWindow == this)
    {
        RLWindow = nullptr;
        glfwTerminate();
    }
}

void glfwWindow::Setup()
{
    if (RLWindow != nullptr && RLWindow != this)
    {
        RL_THROW_EXCEPTION("Too many Windows have been created.");
    }
    RLWindow = this;
}

void glfwWindow::EnableContext()
{
    glfwMakeContextCurrent(window);
}

bool glfwWindow::Update()
{
    input.Update();
    return !glfwWindowShouldClose(window);
}

internal::Input* glfwWindow::GetInput() const
{
    return (internal::Input*)&input;
}

void* glfwWindow::GetHWND() const
{
#ifdef GLFW_EXPOSE_NATIVE_WIN32
    return glfwGetWin32Window(window);
#endif
    return nullptr;
}

void* glfwWindow::GetGLFWwindow() const
{
    return window;
}

int glfwWindow::GetWidth() const
{
    if (isFullscreen)
        return maxWidth;
    return minWidth;
}

int glfwWindow::GetHeight() const
{
    if (isFullscreen)
        return maxHeight;
    return minHeight;
}

void glfwWindow::SetResizeCallback(RLWindowResizeCallback callback)
{
    externalResizeCallback = callback;
}

void glfwWindow::internalResizeCallback(GLFWwindow* window, int width, int height)
{
    if (!Application::IsSetup())
    {
        RL_LOG_ERROR("Window has not been created. Have you Setup the application?");
        return;
    }

    if (width == 0 && height == 0)
        return;

    auto* RLWindow = (glfwWindow*)Application::GetWindowUnsafe();

    if (RLWindow->isFullscreen)
    {
        RLWindow->maxWidth = width;
        RLWindow->maxHeight = height;
    }
    else
    {
        RLWindow->minWidth = width;
        RLWindow->minHeight = height;
    }

    RLWindow->externalResizeCallback(RLWindow, width, height);
}

void glfwWindow::SetFullscreen(bool fullscreen)
{
    isFullscreen = fullscreen;
    if (fullscreen)
    {
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, maxWidth, maxHeight, GLFW_DONT_CARE);
    }
    else
    {
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, minWidth, minHeight, GLFW_DONT_CARE);
    }
}
