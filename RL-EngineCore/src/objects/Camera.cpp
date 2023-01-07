#include "../../include/objects/Camera.h"

using namespace Core;

Camera* Camera::mainCamera = nullptr;

Camera::Camera(Entity* entity, int width, int height) : Entity::Component(entity) {
	mainCamera = this;
	viewWidth = width;
	viewHeight = height;
}

DirectX::XMMATRIX Camera::getViewMatrix() {

	return DirectX::XMMatrixPerspectiveFovLH(fov * pi / 180.0, viewWidth / viewHeight, nearPlane, farPlane);
}

DirectX::XMMATRIX Camera::getPositionMatrix() {

	return DirectX::XMMatrixInverse(nullptr, entity->transform.getMatrix());
}
