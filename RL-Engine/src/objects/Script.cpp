#include "../../include/objects/Script.h"


Engine::Script::Script() : Entity::Component((Entity^)nullptr) 
{
	GetInstance()->setType("Script");
	Start();
}

Engine::Script::Script(Entity^ entity) : Entity::Component(entity)
{
	GetInstance()->setType("Script");
	Start();
}

void Engine::Script::Start() {

}

void Engine::Script::Update()
{
	
}
