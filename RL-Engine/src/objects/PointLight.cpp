#include "../../include/objects/PointLight.h"

using namespace Engine;

PointLight::PointLight(Entity^ entity) : 
	ManagedComponent(new Core::PointLight(entity->GetInstance()), entity)
{
}

void PointLight::setColour(Vec3^ colour)
{
	instance->Colour.x = colour->x;
	instance->Colour.y = colour->y;
	instance->Colour.z = colour->z;
}

void PointLight::setPower(float power)
{
	instance->power = power;
}

void PointLight::setRange(float range)
{
	instance->range = range;
}

Vec3^ PointLight::getColour()
{
	Core::Vec3 temp = instance->Colour;
	return gcnew Vec3(temp.x, temp.y, temp.z);
}

float PointLight::getPower()
{
	return instance->power;
}

float Engine::PointLight::getRange()
{
	return instance->range;
}
