#include "../../include/Objects/Entity.h"


Entity::Entity() : transform(this) {

}

Entity::Transform::Transform(Entity* entity) {
	this->entity = entity;
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

Entity::Transform* Entity::getTransform() {
	return &transform;
}

void Entity::Destroy() {
	//set children parents to this parent
	for (int i = 0; i < getChildCount(); i++) {
		getChild(i)->setParent(parent);
	}
}

//transformation functions

void Entity::Transform::UpdateBuffer(ID3D11Device* device, ID3D11DeviceContext* context, DirectX::XMMATRIX viewMat) {
	
	struct data {
		DirectX::XMMATRIX mat;
	};
	data temp;
	temp.mat = getMatrix();

	//add view matrix
	temp.mat *= viewMat;// DirectX::XMMatrixPerspectiveLH(1, 720.0f / 1280.0f, 0.5f, 10);//need to fix

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(temp);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &temp;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	device->CreateBuffer(&bufferDesc, &initData, &constBuffer);
	context->VSSetConstantBuffers(0, 1, constBuffer.GetAddressOf());

}

DirectX::XMMATRIX Entity::Transform::getMatrix() {

	//reset matrix
	matrix = DirectX::XMMatrixIdentity();

	//local Transformation
	matrix *= DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	//converted to radians
	matrix *= DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);
	matrix *= DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//parent transformation
	if(entity->getParent() != nullptr)
		matrix *= entity->getParent()->getTransform()->getMatrix();

	//return
	updated = true;
	return matrix;
}

//position
void Entity::Transform::setPosition(Vec3 position) {
	updated = false;
	this->position = position;
}

void Entity::Transform::setPosition(float x, float y, float z) {
	updated = false;
	this->position = Vec3(x, y, z);
}

Vec3 Entity::Transform::getPosition() {
	return position;
}

//rotation
void Entity::Transform::setRotation(Vec3 rotation) {
	updated = false;
	this->rotation = rotation;
}

void Entity::Transform::setRotation(float x, float y, float z) {
	updated = false;
	this->rotation = Vec3(x, y, z);
}

Vec3 Entity::Transform::getRotation() {
	return rotation;
}

//scale
void Entity::Transform::setScale(Vec3 scale) {
	updated = false;
	this->scale = scale;
}

void Entity::Transform::setScale(float x, float y, float z) {
	updated = false;
	this->scale = Vec3(x, y, z);
}

void Entity::Transform::setScale(float scale) {
	updated = false;
	this->scale = Vec3(scale, scale, scale);
}

Vec3 Entity::Transform::getScale() {
	return scale;
}
