#pragma once

#include "../../pch.h"
#include "../types/Transform.h"

namespace Engine {
	public ref class Entity : public Managed<Core::Entity>
	{
	public:

		//sub class
		//component
		ref class Component : Managed<Core::Entity::Component> {
		public:
			Component(Entity^ entity);
			Component(Core::Entity::Component* comp);
			Entity^ entity;
		};

		//general
		Entity();
		Entity(Core::Entity* entity);
		void Destroy();
		Transform^ transform;

		//component management
		void addComponent(Component^ component) {
			instance->addComponent(component->GetInstance());
		}

		template<typename T> 
		T^ getComponent() {
			return instance->getComponent<T>();
		}

		template<typename T> 
		T^ removeComponent() {
			return instance->removeComponent<T>();
		}

		//tree management
		//Entity^ getParent();
		//void setParent(Entity^* parent);

		//std::vector<Entity^*> getChildren();//fix?
		//Entity^* getChild(int index);
		//int getChildCount();
	};
}


