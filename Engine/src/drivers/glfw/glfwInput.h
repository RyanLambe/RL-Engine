#pragma once

#include "../../core/Input.h"

namespace rl
{
    class glfwInput : internal::Input
    {
    public:
        ~glfwInput() override = default;

        void Update();

        [[nodiscard]] float GetKey(Key key) const override;
        [[nodiscard]] float GetAxis(const std::string &axis) override;
        [[nodiscard]] glm::vec2 GetMousePos() const override;

        void CreateAxis(const std::string &key, Axis axis) override;

    private:
        std::unordered_map<std::string, Axis> axes = std::unordered_map<std::string, Axis>();
    };
} // namespace rl
