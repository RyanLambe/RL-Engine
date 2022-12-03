#include "../../include/Objects/Entity.h"

void Entity::addComponent(Component* component) {
	components.put(component);
}

Entity* Entity::getParent() {
	return parent;
}

void Entity::setParent(Entity* parent) {
	//remove this from previous parent
	for (int i = 0; i < this->parent->children.size(); i++) {
		if (this->parent->getChild(i) == this)
			this->parent->children.remove(i);
	}

	//add this to new parent
	parent->children.put(this);
	//set parent pointer
	this->parent = parent;
}

LinkedList<Entity*> Entity::getChildren() {
	return children;
}

Entity* Entity::getChild(int index) {
	return children.get(index);
}

int Entity::getChildCount() {
	return children.size();
}

void Entity::Destroy() {
	//set children parents to this parent
	for (int i = 0; i < getChildCount(); i++) {
		getChild(i)->setParent(parent);
	}
}
