#pragma once

#include "../types/LinkedList.h"

class Entity {

public:

	//components that are attatched to Entity
	class Component {};

	//manage components
	void addComponent(Component* component);
	template<typename T> T* getComponent();
	template<typename T> void removeComponent();

	//manage tree
	Entity* getParent();
	void setParent(Entity* parent);

	LinkedList<Entity*> getChildren();
	Entity* getChild(int index);
	int getChildCount();

	//manage transform

	void Destroy();

private:
	//instance variables
	LinkedList<Component*> components;
	Entity* parent;
	LinkedList<Entity*> children;
	//transform???
};

//template function definitions

template<typename T>
inline T* Entity::getComponent() {
	for (int i = 0; i < components.size(); i++) {
		if (dynamic_cast<T*>(components.get(i)) != nullptr)
			return (T*)components.get(i);
	}
	return nullptr;
}

template<typename T>
inline void Entity::removeComponent() {
	for (int i = 0; i < components.size(); i++) {
		if (dynamic_cast<T*>(components.get(i)) != nullptr)
			components.remove(i);
	}
}
