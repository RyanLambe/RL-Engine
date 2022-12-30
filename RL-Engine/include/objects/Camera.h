#pragma once
#include <DirectXMath.h>
//#include "../Graphics.h"
#include "Entity.h"

class Camera : public Entity::Component{
public:

	static Camera* mainCamera;

	Camera(Entity* entity, int width, int height);

	DirectX::XMMATRIX getViewMatrix();
	DirectX::XMMATRIX getPositionMatrix();


	float fov = 90;
	float nearPlane = 0.01f;
	float farPlane = 100.0f;
	float viewWidth;
	float viewHeight;

};