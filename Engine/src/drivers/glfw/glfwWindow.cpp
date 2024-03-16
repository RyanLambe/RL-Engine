#include "glfwWindow.h"

#include <GLFW/glfw3native.h>

#include "../../core/RLResult.h"

using namespace rl;

glfwWindow* glfwWindow::RLWindow = nullptr;

glfwWindow::glfwWindow(int width, int height, const std::string& title, bool fullscreen) {

    if(RLWindow != nullptr){
        RL_THROW_EXCEPTION("Cannot have multiple glfw instances at once");
    }
    RLWindow = this;

    if(!glfwInit()){
        RL_THROW_EXCEPTION("Failed to initialize glfw.");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);

    GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
    if(!window){
        glfwTerminate();
        RL_THROW_EXCEPTION("Failed to create glfw window.");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, internalResizeCallback);

    RLWindow->minWidth = width;
    RLWindow->minHeight = height;
    if(fullscreen){
        RLWindow->maxWidth = width;
        RLWindow->maxHeight = height;
    }
    else{
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        RLWindow->maxWidth = mode->width;
        RLWindow->maxHeight = mode->height;
    }

    isFullscreen = fullscreen;
}

glfwWindow::~glfwWindow() {
    glfwTerminate();
}

bool glfwWindow::Update() const noexcept {
    glfwPollEvents();
    return !glfwWindowShouldClose(window);
}

void* glfwWindow::getHWND() const noexcept {
    #ifdef GLFW_EXPOSE_NATIVE_WIN32
        return glfwGetWin32Window(window);
    #endif
    return nullptr;
}

void *glfwWindow::getGLFWwindow() const noexcept {
    return window;
}

int glfwWindow::getWidth() const noexcept {
    if(isFullscreen)
        return maxWidth;
    return minWidth;
}

int glfwWindow::getHeight() const noexcept {
    if(isFullscreen)
        return maxHeight;
    return minHeight;
}

void glfwWindow::setResizeCallback(RLWindowResizeCallback callback) noexcept {
    externalResizeCallback = callback;
}

void glfwWindow::internalResizeCallback(GLFWwindow *window, int width, int height) {
    if(!RLWindow)
        return;

    if(width == 0 && height == 0)
        return;

    if(RLWindow->isFullscreen){
        RLWindow->maxWidth = width;
        RLWindow->maxHeight = height;
    }
    else{
        RLWindow->minWidth = width;
        RLWindow->minHeight = height;
    }

    RLWindow->externalResizeCallback(RLWindow, width, height);
}

void glfwWindow::setFullscreen(bool fullscreen) noexcept {
    isFullscreen = fullscreen;
    if(fullscreen){
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, maxWidth, maxHeight, GLFW_DONT_CARE);
    }
    else{
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, minWidth, minHeight, GLFW_DONT_CARE);
    }
}

GLFWwindow *glfwWindow::GetActiveGLFWWindow() noexcept {
    return RLWindow->window;
}

glfwWindow *glfwWindow::GetActiveRLWindow() noexcept {
    return RLWindow;
}
