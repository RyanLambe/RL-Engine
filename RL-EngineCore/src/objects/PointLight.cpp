#include "../../include/objects/PointLight.h"

Core::PointLight::PointLight(Entity* entity) : Core::Entity::Component(entity) {
}


//used for light culling
float Core::PointLight::distToCam()
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

float Core::PointLight::distToCam(bool reset)
{
	//this->reset = reset;
	return -1;
}
