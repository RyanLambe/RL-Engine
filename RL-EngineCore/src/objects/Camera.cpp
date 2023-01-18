#include "../../include/objects/Camera.h"

Core::Camera* Core::Camera::mainCamera = nullptr;

Core::Camera::Camera(Entity* entity, int width, int height) : Entity::Component(entity) {
	viewWidth = width;
	viewHeight = height;
}

DirectX::XMMATRIX Core::Camera::getViewMatrix() {

	return DirectX::XMMatrixPerspectiveFovLH(fov * pi / 180.0, viewWidth / viewHeight, nearPlane, farPlane);
}

DirectX::XMMATRIX Core::Camera::getPositionMatrix() {

	return DirectX::XMMatrixInverse(nullptr, entity->transform.getMatrix());
}

Core::Camera* Core::Camera::getMainCamera() {
	if(mainCamera->exists)
		return mainCamera;
	return nullptr;
}

void Core::Camera::setMainCamera(Camera* newMain) {
	mainCamera = newMain;
}
