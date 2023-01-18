#include "../../include/objects/DirectionalLight.h"

using namespace Engine;

DirectionalLight::DirectionalLight(Entity^ entity) : 
	ManagedComponent(Core::Graphics::createDirectionalLight(entity->GetInstance()), entity)
{
	setColour(gcnew Vec3(1));
}

void DirectionalLight::setColour(Vec3^ colour)
{
	instance->Colour.x = colour->x;
	instance->Colour.y = colour->y;
	instance->Colour.z = colour->z;
}

Vec3^ DirectionalLight::getColour()
{
	Vec3^ out;
	out->x = instance->Colour.x;
	out->y = instance->Colour.y;
	out->x = instance->Colour.x;
	return out;
}
