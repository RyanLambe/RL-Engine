#include <algorithm>
#include "Transform.h"

using namespace rl;

const glm::mat4& Transform::GetTransformationMatrix() noexcept
{
    const glm::mat4 pos = glm::translate(glm::mat4(1.0f), position);
    const glm::mat4 rot = glm::mat4_cast(rotation);
    const glm::mat4 sca = glm::scale(glm::mat4(1.0f), scale);
    matrix = pos * rot * sca;
    return matrix;
}

glm::mat4 Transform::GetInverseTransformationMatrix() const noexcept
{
    const glm::vec3 invScaleVec = glm::vec3(1.0f / (scale.x != 0.00f ? scale.x : 1.0f),
                                            1.0f / (scale.y != 0.00f ? scale.y : 1.0f),
                                            1.0f / (scale.z != 0.00f ? scale.z : 1.0f));

    const glm::mat4 invPos = glm::translate(glm::mat4(1.0f), -position);
    const glm::mat4 invRot = glm::mat4_cast(glm::conjugate(rotation));
    const glm::mat4 invScale = glm::scale(glm::mat4(1.0f), invScaleVec);
    return invScale * invRot * invPos;
}

glm::quat Transform::EulerToQuat(const glm::vec3& euler) noexcept
{
    const glm::quat xQ = glm::angleAxis(glm::radians(euler.x), glm::vec3(1, 0, 0));
    const glm::quat yQ = glm::angleAxis(glm::radians(euler.y), glm::vec3(0, 1, 0));
    const glm::quat zQ = glm::angleAxis(glm::radians(euler.z), glm::vec3(0, 0, 1));
    return yQ * xQ * zQ;
}

// todo: check if works properly
glm::vec3 Transform::QuatToEuler(const glm::quat &quat) noexcept
{
    glm::quat q = glm::normalize(quat);
    const float z = ExtractAngleFromQuat(q, glm::vec3(0, 0, 1));
    const float x = ExtractAngleFromQuat(q, glm::vec3(1, 0, 0));
    const float y = ExtractAngleFromQuat(q, glm::vec3(0, 1, 0));
    return {x, y, z};
}

float Transform::ExtractAngleFromQuat(glm::quat &quat, const glm::vec3 &axis) noexcept
{
    const float quatAngle = 2.0f * acosf(quat.w);
    const float div = sinf(quatAngle / 2);
    const glm::vec3 quatAxis = glm::vec3(quat.x, quat.y, quat.z) / glm::vec3(div == 0.000000f ? 0.000001f : div);

    const float f = glm::dot(glm::normalize(quatAxis), axis);
    const float finalAngle = glm::degrees(quatAngle * f);
    quat = glm::normalize(quat * glm::angleAxis(-finalAngle, glm::vec3(0, 0, 1)));

    return finalAngle;
}
