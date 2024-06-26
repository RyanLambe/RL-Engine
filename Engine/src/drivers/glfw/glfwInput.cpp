#include "glfwInput.h"

namespace rl {

    float glfwInput::GetKey(rl::Key key) const {
        return 0;
    }

    float glfwInput::GetAxis(const std::string &axis) const {
        return 0;
    }

    glm::vec2 glfwInput::GetMousePos() const {
        return glm::vec2(0);
    }

    void glfwInput::CreateAxis(const std::string &key, Axis axis) {

    }
}

