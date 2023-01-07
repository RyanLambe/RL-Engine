#include "../../pch.h"
#include "../../include/objects/Camera.h"

Engine::Camera::Camera(Entity^ entity) : 
	ManagedComponent(new Core::Camera(entity->GetInstance(), Core::Graphics::getWidth(), Core::Graphics::getHeight()), entity)
{
	main = this;
}

void Engine::Camera::setFOV(float fov)
{
	instance->fov = fov;
}

void Engine::Camera::setNearPlane(float nearPlane)
{
	instance->nearPlane = nearPlane;
}

void Engine::Camera::setFarPlane(float farPlane)
{
	instance->farPlane = farPlane;
}

float Engine::Camera::getFOV()
{
	return instance->fov;
}

float Engine::Camera::getNearPlane()
{
	return instance->nearPlane;
}

float Engine::Camera::getFarPlane()
{
	return instance->farPlane;
}
