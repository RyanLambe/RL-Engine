#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#ifndef SCRIPT
#define SCRIPT
#include "Entity.h"

namespace Engine {

	public ref class Script : public Entity::Component
	{
	protected:
		Entity^ entity;
		Transform^ transform;

	public:
		Script(Entity^ entity);
		
		//virtual void Start();

		virtual void Update();

	};
}
#endif