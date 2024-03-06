#pragma once

#include "../ecs/Component.h"
#include "glm/glm.hpp"

namespace rl {
    class Transform : public Component<Transform> {
    public:

        glm::vec3 position = glm::vec3(0);
        glm::vec3 rotation = glm::vec3(0);
        glm::vec3 scale = glm::vec3(1);

        // Translate
        void Translate(float x, float y, float z);
        void Translate(glm::vec3 offset);

        void Rotate(float x, float y, float z);
        void Rotate(glm::vec3 offset);

        void Scale(float x);
        void Scale(float x, float y, float z);
        void Scale(glm::vec3 amount);

        // todo: implement forward, right, up
        glm::vec3 forward() const noexcept;
        glm::vec3 right() const noexcept;
        glm::vec3 up() const noexcept;

        // LookAt

        const glm::mat4& GetTransformationMatrix() noexcept;
        glm::mat4 GetInverseTransformationMatrix() const noexcept;

    private:
        glm::mat4 matrix = glm::mat4(1);

        void RecalculateMatrix();
    };
}
