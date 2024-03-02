#pragma once

#include "../ecs/Component.h"
#include "glm/glm.hpp"

namespace rl {
    class Transform : public Component<Transform> {
    public:

        glm::vec3 position = glm::vec3(0);
        glm::vec3 rotation = glm::vec3(0);
        glm::vec3 scale = glm::vec3(1);

        const glm::mat4& GetTransformationMatrix() noexcept;

        // Forward
        // Right
        // Up

        // LookAt

    private:
        glm::mat4 matrix = glm::mat4(1);

        void RecalculateMatrix();
    };
}
