#include "../../include/objects/Entity.h"

using namespace Engine;

//component functions

Entity::Component::Component(Entity^ entity)
{
	if (entity) {
		instance = new Core::Entity::Component(entity->GetInstance());
		this->entity = entity;
		this->transform = entity->transform;
	}
	else
		instance = new Core::Entity::Component(nullptr);
	instanceOnHeap = true;
}

Entity::Component::Component(Core::Entity::Component* comp)
{
	instance = comp;
	instanceOnHeap = false;
	if (comp && comp->entity) {
		this->entity = gcnew Entity(comp->entity);
		this->transform = entity->transform;
	}
}

Entity::Component::~Component() {
	CleanUp();
}

Entity::Component::!Component() {
	CleanUp();
}

void Entity::Component::CleanUp() {
	if (instance == nullptr)
		return;

	if (instanceOnHeap) {
		delete instance;
		return;
	}

	if (((Core::Entity::Component*)instance)->entity == nullptr) {
		((Core::Entity::Component*)instance)->exists = false;
	}
}

void Entity::Component::SetEntity(Entity^ newEntity) {
	
	newEntity->GetInstance()->addComponent(GetInstance());
	entity = newEntity;
	if (entity) {
		GetInstance()->entity = entity->GetInstance();
		transform = entity->transform;
	}
}

Core::Entity::Component* Entity::Component::GetInstance() {
	return (Core::Entity::Component*)instance;
}

//entity functions

Entity::Entity(Core::Entity* entity)
{
	instance = entity;
	if (entity)
		transform = gcnew Transform(&entity->transform);
	else
		transform = nullptr;
}

//tree management

Entity^ Entity::getParent() {
	return gcnew Entity(instance->getParent());
}

void Entity::setParent(Entity^ parent) {
	instance->setParent(parent->GetInstance());
}

int Entity::getChildCount() {
	return instance->getChildCount();
}

Entity^ Entity::getChild(int index) {
	return gcnew Entity(instance->getChild(index));
}

array<Entity^>^ Entity::getChildren() {
	std::vector<Core::Entity*> in = instance->getChildren();
	array<Entity^>^ out = gcnew array<Entity^>(in.size());

	for (int i = 0; i < in.size(); i++)
		out[i] = gcnew Entity(in[i]);
	return out;
}