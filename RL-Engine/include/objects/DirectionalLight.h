#pragma once

#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif
#include "../types/ManagedComponent.h"

namespace Engine {
	public ref class DirectionalLight : public ManagedComponent<Core::DirectionalLight>
	{
	public:

		DirectionalLight(Entity^ entity);

		void setColour(Vec3^ colour);
		Vec3^ getColour();

	};
}