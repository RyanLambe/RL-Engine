#include "../../include/objects/Camera.h"

Engine::Camera::Camera(Entity^ entity) : 
	ManagedComponent(Core::Graphics::createCamera(entity->GetInstance()), entity)
{
	setMain();
}

Engine::Camera^ Engine::Camera::getMain() {
	return main;
}

void Engine::Camera::setMain(Camera^ main) {
	Camera::main = main;
	Core::Camera::setMainCamera(main->GetInstance());
}

void Engine::Camera::setMain() {
	Camera::main = this;
	Core::Camera::setMainCamera(instance);
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
