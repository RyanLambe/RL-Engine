#include "../../include/Objects/Entity.h"
#include "../../include/Debug.h"

using namespace Core;

Entity::Entity() : transform(this) {

}

void Entity::addComponent(Component* component) {
	components.push_back(component);
}

Entity* Entity::getParent() {
	return parent;
}

void Entity::setParent(Entity* parent) {
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

std::vector<Entity*> Entity::getChildren() {
	return children;
}

Entity* Entity::getChild(int index) {
	return children[index];
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
