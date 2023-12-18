#include "PointLight.h"

using namespace rl;

PointLight::PointLight(Entity* entity) : Entity::Component(entity) {
	setType("PointLight");
}


//used for light culling
float PointLight::distToCam()
{
	//if (!reset) {
		//return camDist;
	//}

	//Vec3 pos = entity->getTransform()->getPosition();
	//Vec3 cam = Camera::mainCamera->entity->getTransform()->getPosition();
	//camDist = Vec3::distance(pos, cam);

	reset = false;
	return -1;
	return camDist;
}

float PointLight::distToCam(bool reset)
{
	//this->reset = reset;
	return -1;
}
