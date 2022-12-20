#pragma once
#include "Entity.h"

class DirectionalLight : public Entity::Component {

public:

	DirectionalLight(Entity* entity);

	Vec3 Colour;

};