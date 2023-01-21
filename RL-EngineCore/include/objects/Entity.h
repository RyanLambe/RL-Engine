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

			std::string getType() { return type; }
			void setType(std::string newType) { type = newType; }
		protected:
			std::string type = "Component";
		};

		//general
		Entity();
		~Entity();
		Transform transform;

		//Entity& operator=(const Entity&);

		//manage components
		void addComponent(Component* component);

		Component* getComponent(std::string type);
		std::vector<Component*> getComponents(std::string type);

		Component* removeComponent(std::string type);
		std::vector<Component*> removeComponents(std::string type);

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
}