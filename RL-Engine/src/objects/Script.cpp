#include "../../include/objects/Script.h"


Engine::Script::Script() : Entity::Component((Entity^)nullptr) 
{
	GetInstance()->setType("Script");
}

Engine::Script::Script(Entity^ entity) : Entity::Component(entity)
{
	GetInstance()->setType("Script");
}

void Engine::Script::Start() {

}

void Engine::Script::Update()
{
	
}
