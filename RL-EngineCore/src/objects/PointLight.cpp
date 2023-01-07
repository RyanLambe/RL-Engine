#include "../../include/objects/PointLight.h"

using namespace Core;

PointLight::PointLight(Entity* entity) : Entity::Component(entity) {
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
