#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

using namespace rl;

const glm::mat4 &Transform::GetTransformationMatrix() noexcept {

    RecalculateMatrix();
    return matrix;
}

void Transform::RecalculateMatrix() {
    matrix = glm::translate(glm::mat4(1), position);
    matrix *= glm::toMat4(glm::quat(rotation));
    matrix *= glm::scale(glm::mat4(1), scale);
}
