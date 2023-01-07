#include "../../pch.h"
#include "../../include/objects/Script.h"


Engine::Script::Script(Entity^ entity) : Entity::Component(entity)
{
	this->entity = entity;
	this->transform = entity->transform;
}

void Engine::Script::Update()
{
	//throw gcnew System::NotImplementedException();
}
