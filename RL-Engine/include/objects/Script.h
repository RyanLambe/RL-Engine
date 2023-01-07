#pragma once
#include "../../pch.h"

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


