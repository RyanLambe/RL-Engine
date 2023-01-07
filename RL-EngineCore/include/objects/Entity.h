#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include <vector>
#include <string>

#include "../types/Transform.h"

#include "../types/Vec3.h"
#include "../types/SmartPtr.h"

namespace Core {
	class Entity {
	public:
		//Component subclass
		class Component {
		public:
			Component(Entity* entity) {
				this->entity = entity;
			}

			Entity* entity;

		private:
			//this function makes component polymorphic
			virtual void doNothing() {}
		};

		//general
		Entity();
		void Destroy();
		Transform transform;

		//manage components
		void addComponent(Component* component);
		template<typename T> T* getComponent();
		template<typename T> T* removeComponent();

		//todo: fix tree
		//manage tree
		Entity* getParent();
		void setParent(Entity* parent);

		std::vector<Entity*> getChildren();
		Entity* getChild(int index);
		int getChildCount();

	private:
		Entity* parent = nullptr;
		std::vector<Entity*> children;

		std::vector<Component*> components;
	};

	//template function definitions
	template<typename T>
	inline T* Entity::getComponent() {
		for (int i = 0; i < components.size(); i++) {
			if (dynamic_cast<const T*>(components[i]) != nullptr)
				return (T*)components[i];
		}
		return nullptr;
	}

	template<typename T>
	inline T* Entity::removeComponent() {
		for (int i = 0; i < components.size(); i++) {
			if (dynamic_cast<T*>(components[i]) != nullptr) {
				T* temp = dynamic_cast<T*>(components[i]);
				components.erase(components.begin() + i);
				return temp;
			}
		}
		return nullptr;
	}
}