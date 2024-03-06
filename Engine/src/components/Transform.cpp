#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace rl;


void Transform::Translate(float x, float y, float z)
{
    Translate(glm::vec3(x, y, z));
}

void Transform::Translate(glm::vec3 offset)
{
    this->position += right() * offset.x + up() * offset.y + forward() * offset.z;
}

void Transform::Rotate(float x, float y, float z)
{
    Rotate(glm::vec3(x, y, z));
}

void Transform::Rotate(glm::vec3 offset)
{
    rotation += offset;
}

void Transform::Scale(float x)
{
    Scale(glm::vec3(x));
}

void Transform::Scale(float x, float y, float z)
{
    Scale(glm::vec3(x, y, z));
}

void Transform::Scale(glm::vec3 amount)
{
    scale *= amount;
}

glm::vec3 Transform::forward() const noexcept
{
    return glm::vec3(0, 0, 1);
}

glm::vec3 Transform::right() const noexcept
{
    return glm::vec3(1, 0, 0);
}

glm::vec3 Transform::up() const noexcept
{
    return glm::vec3(0, 1, 0);
}

const glm::mat4& Transform::GetTransformationMatrix() noexcept {

    RecalculateMatrix();
    return matrix;
}

glm::mat4 Transform::GetInverseTransformationMatrix() const noexcept
{
    if (scale.x == 0.0f || scale.y == 0.0f || scale.z == 0.0f)
        return glm::mat4(0);

    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::scale(glm::mat4(1.0f), glm::vec3(1/scale.x, 1/scale.y, 1/scale.z)) * glm::transpose(rotationMatrix) * glm::translate(glm::mat4(1.0f), -position);
}

void Transform::RecalculateMatrix() {

	glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    matrix = glm::translate(glm::mat4(1.0f), position) * rotationMatrix * glm::scale(glm::mat4(1.0f), scale);
}
