#include "Camera.h"

using namespace rl;

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

DirectX::XMMATRIX Camera::getViewMatrix() {

	return DirectX::XMMatrixPerspectiveFovLH(fov * pi / 180.0, viewWidth / viewHeight, max(nearPlane, 0.1f), max(farPlane, 0.5f));
}

DirectX::XMMATRIX Camera::getPositionMatrix() {

	return DirectX::XMMatrixInverse(nullptr, entity->transform.getMatrix());
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
