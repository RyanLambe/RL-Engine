#pragma once

#include "../../pch.h"
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