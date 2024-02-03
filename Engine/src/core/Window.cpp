#include "Window.h"

#include "../drivers/glfw/glfwWindow.h"

namespace rl {
    std::shared_ptr<Window> Window::Create(int width, int height, const std::string& title, bool fullscreen) {
        return std::make_shared<rl::glfwWindow>(width, height, title, fullscreen);
    }
}