#include "../../pch.h"
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
	Managed(new Core::Entity()), transform(gcnew Transform(instance)) {

}

Engine::Entity::Entity(Core::Entity* entity) : 
	Managed(entity), transform(gcnew Transform(instance))
{

}

void Entity::Destroy() {
	instance->Destroy();
}

/*void Engine::Entity::addComponent(Component^ component)
{
	instance->addComponent(component->GetInstance());
}*/
