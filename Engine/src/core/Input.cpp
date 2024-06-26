#include "Input.h"

#include "Application.h"

namespace rl {
    float Input::GetKey(Key key) {
        return Application::GetWindow().GetInput()->GetKey(key);
    }

    float Input::GetAxis(const std::string& axis) {
        return Application::GetWindow().GetInput()->GetAxis(axis);
    }

    glm::vec2 Input::GetMousePos() {
        return Application::GetWindow().GetInput()->GetMousePos();
    }

    void Input::CreateAxis(const std::string& key, Axis axis) {
        Application::GetWindow().GetInput()->CreateAxis(key, axis);
    }
}