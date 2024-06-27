#include "glfwInput.h"

#include <GLFW/glfw3.h>

#include "../../core/Application.h"

namespace rl
{

    void glfwInput::Update()
    {
        glfwPollEvents();
        // update deltas?
    }

    float glfwInput::GetKey(rl::Key key) const
    {
        if (key.GetMethod() == Key::Method::None)
            return 0;

        const auto window = (GLFWwindow*)Application::GetWindow().GetGLFWwindow();
        if (!window)
            RL_LOG_ERROR("Cannot access input. No glfw window has been created");

        switch (key.GetMethod())
        {
            case Key::Method::Keyboard:
                return glfwGetKey(window, (int)key.GetValue().keyboard) == GLFW_PRESS;

            case Key::Method::Mouse:
                return (float)glfwGetMouseButton(window, (int)key.GetValue().mouse) == GLFW_PRESS;

            default:
                return 0;
        }
    }

    float glfwInput::GetAxis(const std::string& axis)
    {
        if (!axes.contains(axis))
        {
            RL_LOG_WARNING("The Axis ", axis, " does not exist.");
            return 0;
        }

        float total = 0;
        for (const auto pair : axes[axis].keys)
        {
            total += GetKey(pair.first) * pair.second;
        }
        return total;
    }

    glm::vec2 glfwInput::GetMousePos() const
    {
        if (!Application::GetWindow().GetGLFWwindow())
        {
            RL_LOG_ERROR("Cannot access input. No glfw window has been created");
            return {0.0f, 0.0f};
        }

        double x, y;
        glfwGetCursorPos((GLFWwindow*)Application::GetWindow().GetGLFWwindow(), &x, &y);
        x /= Application::GetWindow().GetWidth();
        y /= Application::GetWindow().GetHeight();
        return {(float)x, (float)y};
    }

    void glfwInput::CreateAxis(const std::string& key, Axis axis)
    {
        if (axes.contains(key))
        {
            RL_LOG_WARNING("The Axis ", key, " has already been created.");
            return;
        }
        axes[key] = axis;
    }
} // namespace rl
