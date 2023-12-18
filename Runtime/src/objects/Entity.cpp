#include "Entity.h"

using namespace rl;

Entity::Entity() : transform(this) {

}

Entity::~Entity()
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

/*Entity& Entity::operator=(const Entity& other) {
	this->parent = other.parent;
	this->children = other.children;
	this->components = other.components;

	this->transform = other.transform;
}*/

void Entity::addComponent(Component* component) {
	components.push_back(component);
}

Entity::Component* Entity::getComponent(std::string type) {
	for (int i = 0; i < components.size(); i++)
		if (components[i]->getType() == type)
			return components[i];
	return nullptr;
}

std::vector<Entity::Component*> Entity::getComponents(std::string type) {
	std::vector<Component*> out = std::vector<Component*>();
	for (int i = 0; i < components.size(); i++)
		if (components[i]->getType() == type)
			out.push_back(components[i]);
	return out;
}

Entity::Component* Entity::removeComponent(std::string type) {
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->getType() == type) {
			Component* out = components[i];
			components[i]->entity = nullptr;
			components.erase(components.begin() + i);
			return out;
		}
	}
	return nullptr;
}

std::vector<Entity::Component*> Entity::removeComponents(std::string type) {
	std::vector<Component*> out = std::vector<Component*>();
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->getType() == type) {
			out.push_back(components[i]);
			components[i]->entity = nullptr;
			components.erase(components.begin() + i);
		}
	}
	return out;
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
