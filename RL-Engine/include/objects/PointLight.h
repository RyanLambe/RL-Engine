#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "Entity.h"

namespace Engine {
	public ref class PointLight : public Entity::Component
	{
	public:
		PointLight();
		PointLight(Entity^ entity);
		PointLight(Core::PointLight* light);

		static PointLight^ CastAs(Entity::Component^ component);

		void setColour(Vec3^ colour);
		void setPower(float power);
		void setRange(float range);

		Vec3^ getColour();
		float getPower();
		float getRange();
	};
}