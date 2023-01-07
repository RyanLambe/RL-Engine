#pragma once
#include <DirectXMath.h>
#include "Entity.h"

namespace Core {
	class Camera : public Entity::Component {
	public:

		static Camera* mainCamera;

		Camera(Entity* entity, int width, int height);

		DirectX::XMMATRIX getViewMatrix();
		DirectX::XMMATRIX getPositionMatrix();


		float fov = 90;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		float viewWidth;
		float viewHeight;

	};
}
