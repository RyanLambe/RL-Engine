#pragma once

#include <vector>
#include <string>

#include "../types/Transform.h"

namespace Core {
	class Entity {
	public:
		//Component subclass
		class Component {
		public:
			Component(Entity* entity) : entity(entity), exists(true) { }

			Entity* entity = nullptr;
			bool exists = false;

			virtual std::string getType() { return "Component"; }
		};

		//general
		Entity();
		Entity(const Entity&) = delete;
		~Entity();
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