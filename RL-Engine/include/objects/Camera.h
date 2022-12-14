#pragma once
#include <DirectXMath.h>
#include "Entity.h"

class Camera : public Entity::Component{
public:

	static Camera* mainCamera;

	Camera(Entity* entity);

	DirectX::XMMATRIX getViewMatrix();


	bool perspective = true;
	float fov = 90;
	float nearPlane = 0.01f;
	float farPlane = 100.0f;
	float viewWidth;
	float viewHeight;

};