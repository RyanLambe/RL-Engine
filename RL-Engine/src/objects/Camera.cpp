#include "../../include/objects/Camera.h"

Camera* Camera::mainCamera = nullptr;

Camera::Camera(Entity* entity) : Entity::Component(entity) {
	mainCamera = this;
}

DirectX::XMMATRIX Camera::getViewMatrix() {

	DirectX::XMMATRIX pos = DirectX::XMMatrixInverse(nullptr, entity->getTransform()->getMatrix());

	if(perspective)
		return pos * DirectX::XMMatrixPerspectiveFovLH(fov * pi / 180.0, 16.0f / 9.0f, nearPlane, farPlane);

	return pos * DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, farPlane, farPlane);
}
