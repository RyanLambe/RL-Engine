#pragma once

#include "../types/LinkedList.h"

class Node {

public:

	//manage tree
	Node* getParent();

	template<class T>
	LinkedList<T*> getChildrenOfType();
	LinkedList<Node*> getChildren();
	int getChildCount();

	Node* getChild(int index);
	void addChild(Node child);

	Node removeChild(int index);

	//manage transform

private:
	
	Node* parent;
	LinkedList<Node> children;
	//transform

};

//template class needs to be defined in .h file
template<class T>
inline LinkedList<T*> Node::getChildrenOfType() {
	
	LinkedList<T*> out;
	
	//add all children with the same type
	for (int i = 0; i < children.size(); i++) {
		if (dynamic_cast<T*>(&children.get(i)) != nullptr)
			out.put(&children.get(i));
	}

	return out;
}
