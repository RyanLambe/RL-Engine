#include "../../include/objects/PointLight.h"

using namespace Engine;

PointLight::PointLight() :
	Entity::Component(Core::Graphics::createPointLight(nullptr)) {
}

PointLight::PointLight(Entity^ entity) : 
	Entity::Component(Core::Graphics::createPointLight(entity->GetInstance()))
{
}

PointLight::PointLight(Core::PointLight* light) :
	Entity::Component(light) {
}

PointLight^ PointLight::CastAs(Entity::Component^ component) {
	if (component == nullptr)
		return nullptr;
	if (component->GetInstance())
		return gcnew PointLight((Core::PointLight*)component->GetInstance());
	return nullptr;
}

void PointLight::setColour(Vec3^ colour)
{
	GetInstance<Core::PointLight>()->Colour.x = colour->x;
	GetInstance<Core::PointLight>()->Colour.y = colour->y;
	GetInstance<Core::PointLight>()->Colour.z = colour->z;
}

void PointLight::setPower(float power)
{
	GetInstance<Core::PointLight>()->power = power;
}

void PointLight::setRange(float range)
{
	GetInstance<Core::PointLight>()->range = range;
}

Vec3^ PointLight::getColour()
{
	Core::Vec3 temp = GetInstance<Core::PointLight>()->Colour;
	return gcnew Vec3(temp.x, temp.y, temp.z);
}

float PointLight::getPower()
{
	return GetInstance<Core::PointLight>()->power;
}

float Engine::PointLight::getRange()
{
	return GetInstance<Core::PointLight>()->range;
}
