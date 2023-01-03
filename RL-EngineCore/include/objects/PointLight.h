#pragma once
#include "Entity.h"
#include "Camera.h"

class PointLight : public Entity::Component {
public:

	PointLight(Entity* entity);

	Vec3 Colour;

	float power = 1;
	float range = 10;

	//used for light culling
	float distToCam();
	float distToCam(bool reset);

private:
	//used for light culling
	bool reset = true;
	float camDist;

};