#pragma once
#include "Entity.h"

namespace rl {
	class DirectionalLight : public Entity::Component {

	public:

		DirectionalLight(Entity* entity);

		Vec3 Colour = Vec3(1);

	};
}