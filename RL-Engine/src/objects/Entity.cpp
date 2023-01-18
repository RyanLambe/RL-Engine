#include "../../include/objects/Entity.h"

using namespace Engine;

Entity::Component::Component(Entity^ entity) : 
	Managed(new Core::Entity::Component(entity->GetInstance())) 
{
	this->entity = entity;
}

Engine::Entity::Component::Component(Core::Entity::Component* comp) : 
	Managed(comp)
{
	this->entity = gcnew Entity(comp->entity);
}

Entity::Entity() : 
	Managed(new Core::Entity()) {
	transform = gcnew Transform(&instance->transform);
}

Engine::Entity::Entity(Core::Entity* entity) : 
	Managed(entity)
{
	transform = gcnew Transform(&entity->transform);
}

void Entity::Destroy() {
	//destroy in scene when added
	instance->~Entity();
	instance = nullptr;
}

/*void Engine::Entity::addComponent(Component^ component)
{
	instance->addComponent(component->GetInstance());
}*/
