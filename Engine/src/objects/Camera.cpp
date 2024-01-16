#include "Camera.h"

using namespace rl;

#include <glm/gtc/matrix_transform.hpp>

Camera* Camera::mainCamera = nullptr;
float Camera::viewWidth = 0;
float Camera::viewHeight = 0;

Camera::Camera(Entity* entity) : Entity::Component(entity) {
	setType("Camera");
	setMainCamera(this);
}

Camera::~Camera() {
	if (mainCamera == this)
		mainCamera = nullptr;
}

glm::mat4 Camera::getViewMatrix() {

    return glm::perspectiveFovLH(glm::radians(fov), viewWidth, viewHeight,  std::max(nearPlane, 0.1f), std::max(farPlane, 0.5f));
}

glm::mat4 Camera::getPositionMatrix() {

    return glm::inverse(entity->transform.getMatrix());
}

Camera* Camera::getMainCamera() {
	if (mainCamera == nullptr)
		return nullptr;
	if(mainCamera->exists)
		return mainCamera;
	return nullptr;
}

void Camera::setMainCamera(Camera* newMain) {
	mainCamera = newMain;
}
