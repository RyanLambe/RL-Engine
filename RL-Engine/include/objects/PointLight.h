#pragma once
#include "Entity.h"

class PointLight : public Entity::Component {
public:

	PointLight(Entity* entity);

	Vec3 Colour;

	float power = 1;
	float range = 10;

};