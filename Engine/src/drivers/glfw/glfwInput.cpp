#include "../../core/Input.h"

#include "glfwWindow.h"
#include "../../core/RLResult.h"
#include "../../core/Application.h"

bool rl::Input::GetKey(Key key) {

    if(!Application::GetWindow().getGLFWwindow())
        RL_THROW_EXCEPTION("Cannot access input. No glfw window has been created");

    return glfwGetKey((GLFWwindow*)Application::GetWindow().getGLFWwindow(), (int)key) == GLFW_PRESS;
}

extern bool rl::Input::GetMouseButton(MouseButton button) {
    if(!Application::GetWindow().getGLFWwindow())
        RL_THROW_EXCEPTION("Cannot access input. No glfw window has been created");

    return glfwGetMouseButton((GLFWwindow*)Application::GetWindow().getGLFWwindow(), (int)button) == GLFW_PRESS;
}

extern glm::vec2 rl::Input::GetMousePos() {
    if(!Application::GetWindow().getGLFWwindow())
        RL_THROW_EXCEPTION("Cannot access input. No glfw window has been created");

    double x, y;
    glfwGetCursorPos((GLFWwindow*)Application::GetWindow().getGLFWwindow(), &x, &y);
    x /= Application::GetWindow().getWidth();
    y /= Application::GetWindow().getHeight();
    return glm::vec2((float)x, (float)y);
}