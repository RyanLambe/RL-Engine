#pragma once
#include <DirectXMath.h>
#include "Entity.h"

namespace Core {
	class Camera : public Entity::Component {
	public:

		//Camera() = delete;
		Camera(Entity* entity, int width, int height);
		//Camera(const Camera&) = delete;

		std::string getType() override { return "Camera"; }

		DirectX::XMMATRIX getViewMatrix();
		DirectX::XMMATRIX getPositionMatrix();

		//camera to render
		static Camera* getMainCamera();
		static void setMainCamera(Camera* newMain);

		//settings
		float fov = 90;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		float viewWidth;
		float viewHeight;

	private:
		static Camera* mainCamera;

	};
}