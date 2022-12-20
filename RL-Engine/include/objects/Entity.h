#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <string>

#include "../types/Vec3.h"

#define pi 3.141592653589793238463

class Entity {

//subclasses
public:
	class Component {
	public:
		Component(Entity* entity) {
			this->entity = entity;
		}

		Entity* entity;

	private:
		//this function makes component polymorphic
		virtual void doNothing() {}
	};

private:
	class Transform {
	public:
		//engine use
		Transform(Entity* entity);
		void UpdateBuffer(ID3D11Device* device, ID3D11DeviceContext* context);
		DirectX::XMMATRIX getMatrix();
		
		//transformation functions
		void setPosition(Vec3 position);
		void setPosition(float x, float y, float z);
		Vec3 getPosition();

		void setRotation(Vec3 rotation);
		void setRotation(float x, float y, float z);
		Vec3 getRotation();

		void setScale(Vec3 scale);
		void setScale(float x, float y, float z);
		void setScale(float scale);
		Vec3 getScale();

	private:
		//constant buffer data
		bool updated = false;
		DirectX::XMMATRIX matrix;
		Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer;

		//transform data
		Entity* entity;
		Vec3 position;
		Vec3 rotation;
		Vec3 scale = Vec3(1);
	};

//entity functions
public:

	//general
	Entity();
	void Destroy();
	Transform* getTransform();

	//manage components
	void addComponent(Component* component);
	template<typename T> T* getComponent();
	template<typename T> void removeComponent();

	//todo: fix tree
	//manage tree
	Entity* getParent();
	void setParent(Entity* parent);

	std::vector<Entity*> getChildren();
	Entity* getChild(int index);
	int getChildCount();


//instance variables
private:
	std::vector<Component*> components;
	Entity* parent;
	std::vector<Entity*> children;
	Transform transform;
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
inline void Entity::removeComponent() {
	for (int i = 0; i < components.size(); i++) {
		if (dynamic_cast<T*>(components[i]) != nullptr)
			components.erase(components.begin() + i);
	}
}
