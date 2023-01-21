#pragma once

#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "Entity.h"

namespace Engine {
	public ref class DirectionalLight : public Entity::Component
	{
	public:
		DirectionalLight();
		DirectionalLight(Entity^ entity);
		DirectionalLight(Core::DirectionalLight* light);

		static DirectionalLight^ CastAs(Entity::Component^ component);

		void setColour(Vec3^ colour);
		Vec3^ getColour();

	};
}