#pragma once

#include "../../core/Input.h"

namespace rl {
    class glfwInput : internal::Input {
    public:
        ~glfwInput() override = default;

        [[nodiscard]] float GetKey(Key key) const override;
        [[nodiscard]] float GetAxis(const std::string& axis) const override;
        [[nodiscard]] glm::vec2 GetMousePos() const override;

        void CreateAxis(const std::string& key, Axis axis) override;

    private:
        // ???
    };
}
