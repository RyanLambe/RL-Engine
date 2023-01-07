#pragma once
#include "../../pch.h"

#include "../types/ManagedComponent.h"

namespace Engine {
	public ref class PointLight : public ManagedComponent<Core::PointLight> {
	public:

		PointLight(Entity^ entity);

		void setColour(Vec3^ colour);
		void setPower(float power);
		void setRange(float range);

		Vec3^ getColour();
		float getPower();
		float getRange();
	};
}