#include "../../include/Objects/Entity.h"

Core::Entity::Entity() : transform(this) {

}

Core::Entity::~Entity()
{
	//set children parents to this parent
	for (int i = 0; i < getChildCount(); i++) {
		getChild(i)->setParent(parent);
	}

	//mark components as deleted
	for (int i = 0; i < components.size(); i++) {
		components[i]->exists = false;
	}
}

void Core::Entity::addComponent(Component* component) {
	components.push_back(component);
}

Core::Entity* Core::Entity::getParent() {
	return parent;
}

void Core::Entity::setParent(Entity* parent) {
	//remove this from previous parent
	if (this->parent != nullptr) {
		for (int i = 0; i < this->parent->children.size(); i++) {
			if (this->parent->getChild(i) == this)
				this->parent->children.erase(this->parent->children.begin() + i);
		}
	}

	//add this to new parent
	if (parent != nullptr) {
		parent->children.push_back(this);
	}
	//set parent pointer
	this->parent = parent;
}

std::vector<Core::Entity*> Core::Entity::getChildren() {
	return children;
}

Core::Entity* Core::Entity::getChild(int index) {
	return children[index];
}

int Core::Entity::getChildCount() {
	return children.size();
}
