#include "../../core/Input.h"

#include "glfwWindow.h"
#include "../../core/RLResult.h"

bool rl::Input::GetKey(Key key) {
    if(!glfwWindow::GetActiveGLFWWindow())
        RL_THROW_EXCEPTION("Cannot access input. No window has been created");

    return glfwGetKey(glfwWindow::GetActiveGLFWWindow(), (int)key) == GLFW_PRESS;
}

extern bool rl::Input::GetMouseButton(MouseButton button) {
    if(!glfwWindow::GetActiveGLFWWindow())
        RL_THROW_EXCEPTION("Cannot access input. No window has been created");

    return glfwGetMouseButton(glfwWindow::GetActiveGLFWWindow(), (int)button) == GLFW_PRESS;
}

extern glm::vec2 rl::Input::GetMousePos() {
    if(!glfwWindow::GetActiveGLFWWindow())
        RL_THROW_EXCEPTION("Cannot access input. No window has been created");

    double x, y;
    glfwGetCursorPos(glfwWindow::GetActiveGLFWWindow(), &x, &y);
    x /= glfwWindow::GetActiveRLWindow()->getWidth();
    y /= glfwWindow::GetActiveRLWindow()->getHeight();
    return glm::vec2((float)x, (float)y);
}