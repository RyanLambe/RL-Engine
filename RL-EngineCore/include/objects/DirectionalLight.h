#pragma once
#include "Entity.h"

namespace Core {
	class DirectionalLight : public Entity::Component {

	public:

		DirectionalLight(Entity* entity);

		Vec3 Colour;

	};
}