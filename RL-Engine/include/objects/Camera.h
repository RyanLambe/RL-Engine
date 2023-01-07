#pragma once

#include "../../pch.h"
#include "../types/ManagedComponent.h"

namespace Engine {
	public ref class Camera : public ManagedComponent<Core::Camera>
	{
	public:

		static Camera^ main;

		Camera(Entity^ entity);

		void setFOV(float fov);
		void setNearPlane(float nearPlane);
		void setFarPlane(float farPlane);

		float getFOV();
		float getNearPlane();
		float getFarPlane();
	};
}


