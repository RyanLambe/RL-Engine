#include "Window.h"

#include "../drivers/glfw/glfwWindow.h"

std::shared_ptr<rl::Window> rl::Window::Create(int width, int height, const std::string& title, bool fullscreen)
{
    return std::make_shared<rl::glfwWindow>(width, height, title, fullscreen);
}