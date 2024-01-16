#pragma once
#include <DirectXMath.h>
#include "Entity.h"

namespace rl {
	class Camera : public Entity::Component {
	public:

		Camera(Entity* entity);
		~Camera();

		glm::mat4 getViewMatrix();
        glm::mat4 getPositionMatrix();

		//camera to render
		static Camera* getMainCamera();
		static void setMainCamera(Camera* newMain);

		//settings
		float fov = 90;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		static float viewWidth;
		static float viewHeight;

	private:
		static Camera* mainCamera;

	};
}