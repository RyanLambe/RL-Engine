#include "../../include/Objects/Node.h"

Node* Node::getParent() {
	return parent;
}

LinkedList<Node*> Node::getChildren() {
	LinkedList<Node*> out;

	//add all children
	for (int i = 0; i < children.size(); i++) 
		out.put(&children.get(i));
	
	return out;
}

int Node::getChildCount() {
	return children.size();
}

Node* Node::getChild(int index) {
	return &children.get(index);
}

void Node::addChild(Node child) {
	child.parent = this;
	children.put(child);
}

Node Node::removeChild(int index) {
	Node out = children.get(index);
	children.remove(index);
	out.parent = nullptr;
	return out;
}
