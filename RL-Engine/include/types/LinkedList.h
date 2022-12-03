#pragma once

//class definition

template<typename T>
class LinkedList {

public:
	LinkedList();
	LinkedList(T data);
	LinkedList(T data[]);
	~LinkedList();

	void put(T data);
	void set(unsigned int index, T data);

	T get(unsigned int index);
	T* getArray();

	void remove(unsigned int index);
	void clear();

	int size();

private:
	struct Node {
		T data;
		Node* next;
	};

	Node* getNode(unsigned int index);

	Node* root = nullptr;
	int count = 0;
	T* arr = nullptr;
};

//function definitions

//constructor without input
template<typename T>
inline LinkedList<T>::LinkedList() {
}

//constructor with 1 input
template<typename T>
inline LinkedList<T>::LinkedList(T data) {
	put(data);
}

//constructor with more than 1 input
template<typename T>
inline LinkedList<T>::LinkedList(T data[]) {
	for (int i = 0; i < sizeof(data) / sizeof(T); i++)
		put(data[i]);
}

//destructor
template<typename T>
inline LinkedList<T>::~LinkedList() {
	if (arr != nullptr)
		delete arr;
}

//add input data to end of list
template<typename T>
inline void LinkedList<T>::put(T data) {

	//create node
	Node* newNode = new Node();
	if (newNode == nullptr) {
		//throw error malloc
	}

	newNode->data = data;
	newNode->next = nullptr;

	//set node
	if (root == nullptr)
		root = newNode;
	else
		getNode(size() - 1)->next = newNode;

	count++;
}

//set data at input index
template<typename T>
inline void LinkedList<T>::set(unsigned int index, T data) {
	getNode(index)->data = data;
}

//returns data at input index
template<typename T>
inline T LinkedList<T>::get(unsigned int index) {
	return getNode(index)->data;
}

//fills input array pointer with all values in linked list
//Note: Array is deleted when called again
template<typename T>
inline T* LinkedList<T>::getArray() {
	if (arr != nullptr)
		delete arr;
	arr = new T[size()];

	Node* cur = root;
	for (int i = 0; i < size(); i++) {
		arr[i] = cur->data;
		cur = cur->next;
	}

	return arr;
}

//removes node from list
template<typename T>
inline void LinkedList<T>::remove(unsigned int index) {

	Node* node = getNode(index);

	if (index == 0)
		root = node->next;
	else
		getNode(index - 1)->next = node->next;

	delete node;

	count--;
}

//removes all elements from list
template<typename T>
inline void LinkedList<T>::clear() {
	for (int i = 0; i < size(); i++) {
		remove(0);
	}
	count = 0;
	root = nullptr;
}

//gets number of elements in list
template<typename T>
inline int LinkedList<T>::size() {
	return count;
}

//helper method to get pointer the node from index
template<typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::getNode(unsigned int index) {
	Node* curr = root;
	for (int i = 0; i < index; i++) {
		curr = curr->next;
	}

	return curr;
}