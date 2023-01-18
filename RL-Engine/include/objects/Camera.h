#pragma once

#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "../types/ManagedComponent.h"

namespace Engine {
	public ref class Camera : public ManagedComponent<Core::Camera>
	{
	public:

		Camera(Entity^ entity);

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

