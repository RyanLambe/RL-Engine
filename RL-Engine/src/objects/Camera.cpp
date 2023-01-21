#include "../../include/objects/Camera.h"

Engine::Camera::Camera() :
	Entity::Component(Core::Graphics::createCamera(nullptr)) {
	setMain();
}

Engine::Camera::Camera(Entity^ entity) : 
	Entity::Component(Core::Graphics::createCamera(entity->GetInstance()))
{
	setMain();
}

Engine::Camera::Camera(Core::Camera* cam) : Entity::Component(cam) 
{ 

}

Engine::Camera^ Engine::Camera::CastAs(Entity::Component^ component) {
	if (component == nullptr)
		return nullptr;
	if (component->GetInstance())
		return gcnew Camera((Core::Camera*)component->GetInstance());
	return nullptr;
}

Engine::Camera^ Engine::Camera::getMain() {
	return main;
}

void Engine::Camera::setMain(Camera^ main) {
	Camera::main = main;
	Core::Camera::setMainCamera(main->GetInstance<Core::Camera>());
}

void Engine::Camera::setMain() {
	Camera::main = this;
	Core::Camera::setMainCamera((Core::Camera*)instance);
}

void Engine::Camera::setFOV(float fov)
{
	GetInstance<Core::Camera>()->fov = fov;
}

void Engine::Camera::setNearPlane(float nearPlane)
{
	GetInstance<Core::Camera>()->nearPlane = nearPlane;
}

void Engine::Camera::setFarPlane(float farPlane)
{
	GetInstance<Core::Camera>()->farPlane = farPlane;
}

float Engine::Camera::getFOV()
{
	return GetInstance<Core::Camera>()->fov;
}

float Engine::Camera::getNearPlane()
{
	return GetInstance<Core::Camera>()->nearPlane;
}

float Engine::Camera::getFarPlane()
{
	return GetInstance<Core::Camera>()->farPlane;
}
