#pragma once
#include "Entity.h"

namespace Core {
	class DirectionalLight : public Entity::Component {

	public:

		DirectionalLight(Entity* entity);

		std::string getType() override { return "DirectionalLight"; }

		Vec3 Colour;

	};
}