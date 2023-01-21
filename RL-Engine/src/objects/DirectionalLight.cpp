#include "../../include/objects/DirectionalLight.h"

using namespace Engine;

DirectionalLight::DirectionalLight() :
	Entity::Component(Core::Graphics::createDirectionalLight(nullptr)) 
{

}

DirectionalLight::DirectionalLight(Entity^ entity) : 
	Entity::Component(Core::Graphics::createDirectionalLight(entity->GetInstance()))
{

}

DirectionalLight::DirectionalLight(Core::DirectionalLight* light) : Entity::Component(light) 
{

}

DirectionalLight^ DirectionalLight::CastAs(Entity::Component^ component) {
	if (component == nullptr)
		return nullptr;
	if (component->GetInstance())
		return gcnew DirectionalLight((Core::DirectionalLight*)component->GetInstance());
	return nullptr;
}

void DirectionalLight::setColour(Vec3^ colour)
{
	GetInstance<Core::DirectionalLight>()->Colour.x = colour->x;
	GetInstance<Core::DirectionalLight>()->Colour.y = colour->y;
	GetInstance<Core::DirectionalLight>()->Colour.z = colour->z;
}

Vec3^ DirectionalLight::getColour()
{
	Vec3^ out;
	out->x = GetInstance<Core::DirectionalLight>()->Colour.x;
	out->y = GetInstance<Core::DirectionalLight>()->Colour.y;
	out->x = GetInstance<Core::DirectionalLight>()->Colour.x;
	return out;
}
