#include "../../include/objects/Camera.h"

Camera* Camera::mainCamera = nullptr;

Camera::Camera(Entity* entity) : Entity::Component(entity) {
	mainCamera = this;
}

DirectX::XMMATRIX Camera::getViewMatrix() {

	if(perspective)
		return DirectX::XMMatrixPerspectiveFovRH(fov * pi / 180.0, 16.0f / 9.0f, nearPlane, farPlane);

	return DirectX::XMMatrixOrthographicRH(viewWidth, viewHeight, farPlane, farPlane);
}

DirectX::XMMATRIX Camera::getPositionMatrix() {

	return DirectX::XMMatrixInverse(nullptr, entity->getTransform()->getMatrix());
}
