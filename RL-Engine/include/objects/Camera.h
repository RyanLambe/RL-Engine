#pragma once

#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "Entity.h"

namespace Engine {
	public ref class Camera : public Entity::Component
	{
	public:
		Camera();
		Camera(Entity^ entity);
		Camera(Core::Camera* cam);

		static Camera^ CastAs(Entity::Component^ component);

		static Camera^ getMain();
		static void setMain(Camera^ main);
		void setMain();

		void setFOV(float fov);
		void setNearPlane(float nearPlane);
		void setFarPlane(float farPlane);

		float getFOV();
		float getNearPlane();
		float getFarPlane();

	private:
		static Camera^ main;
	};

}

