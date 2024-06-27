#pragma once

#include "../ecs/Component.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace rl
{
    class Transform : public Component<Transform>
    {
    public:
        // instance variables
        glm::vec3 position = glm::vec3(0);
        glm::quat rotation = glm::quat(1, 0, 0, 0);
        glm::vec3 scale = glm::vec3(1);

        // set values
        inline void SetPosition(float x, float y, float z) noexcept
        {
            position = glm::vec3(x, y, z);
        }
        inline void SetPosition(const glm::vec3& pos) noexcept
        {
            position = pos;
        }

        inline void SetRotation(float x, float y, float z) noexcept
        {
            rotation = EulerToQuat(glm::vec3(x, y, z));
        }
        inline void SetRotation(const glm::vec3& rot) noexcept
        {
            rotation = EulerToQuat(rot);
        }
        inline void SetRotation(float angle, const glm::vec3& axis) noexcept
        {
            rotation = glm::angleAxis(glm::radians(angle), axis);
        }

        inline void SetScale(float x) noexcept
        {
            scale = glm::vec3(x);
        }
        inline void SetScale(float x, float y, float z) noexcept
        {
            scale = glm::vec3(x, y, z);
        }
        inline void SetScale(const glm::vec3& newScale) noexcept
        {
            scale = newScale;
        }

        // get values
        [[nodiscard]] inline const glm::vec3& GetPosition() const noexcept
        {
            return position;
        }
        [[nodiscard]] inline const glm::quat& GetRotation() const noexcept
        {
            return rotation;
        }
        [[nodiscard]] inline const glm::vec3& GetScale() const noexcept
        {
            return scale;
        }
        [[nodiscard]] inline glm::vec3 EulerAngles() const noexcept
        {
            return QuatToEuler(rotation);
        }

        // offset
        inline void Translate(float x, float y, float z) noexcept
        {
            position += rotation * glm::vec3(x, y, z);
        }
        inline void Translate(const glm::vec3& offset) noexcept
        {
            position += rotation * offset;
        }

        inline void Rotate(float x, float y, float z) noexcept
        {
            rotation *= EulerToQuat(glm::vec3(x, y, z));
        }
        inline void Rotate(const glm::vec3& offset) noexcept
        {
            rotation *= EulerToQuat(offset);
        }
        inline void Rotate(float angle, const glm::vec3& axis) noexcept
        {
            rotation *= glm::angleAxis(glm::radians(angle), axis);
        }

        inline void Scale(float x) noexcept
        {
            scale *= glm::vec3(x);
        }
        inline void Scale(float x, float y, float z) noexcept
        {
            scale *= glm::vec3(x, y, z);
        }
        inline void Scale(const glm::vec3& amount) noexcept
        {
            scale *= amount;
        }

        // get matrices
        [[nodiscard]] const glm::mat4& GetTransformationMatrix() noexcept;
        [[nodiscard]] glm::mat4 GetInverseTransformationMatrix() const noexcept;

        static glm::quat EulerToQuat(const glm::vec3& euler) noexcept;
        static glm::vec3 QuatToEuler(const glm::quat& quat) noexcept;
        static float ExtractAngleFromQuat(glm::quat& quat, const glm::vec3& axis) noexcept;

    private:
        glm::mat4 matrix = glm::mat4(1);
    };
} // namespace rl
