#include "../../include/objects/Camera.h"

Core::Camera* Core::Camera::mainCamera = nullptr;
float Core::Camera::viewWidth = 0;
float Core::Camera::viewHeight = 0;

Core::Camera::Camera(Entity* entity) : Entity::Component(entity) {
	setType("Camera");
	setMainCamera(this);
}

Core::Camera::~Camera() {
	if (mainCamera == this)
		mainCamera = nullptr;
}

DirectX::XMMATRIX Core::Camera::getViewMatrix() {

	return DirectX::XMMatrixPerspectiveFovLH(fov * pi / 180.0, viewWidth / viewHeight, max(nearPlane, 0.1f), max(farPlane, 0.5f));
}

DirectX::XMMATRIX Core::Camera::getPositionMatrix() {

	return DirectX::XMMatrixInverse(nullptr, entity->transform.getMatrix());
}

Core::Camera* Core::Camera::getMainCamera() {
	if (mainCamera == nullptr)
		return nullptr;
	if(mainCamera->exists)
		return mainCamera;
	return nullptr;
}

void Core::Camera::setMainCamera(Camera* newMain) {
	mainCamera = newMain;
}
