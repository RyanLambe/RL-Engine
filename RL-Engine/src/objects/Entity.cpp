#include "../../include/Objects/Entity.h"
#include "../../include/Debug.h"


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

void Entity::Transform::UpdateBuffer(ID3D11Device* device, ID3D11DeviceContext* context) {
	
	DirectX::XMMATRIX mat = getMatrix();

	if (!bufferCreated) {
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(mat);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &mat;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		Debug::logErrorCode(device->CreateBuffer(&bufferDesc, &initData, &constBuffer));

		bufferCreated = true;
	}
	//update buffer
	else {
		//get location of buffer
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		memset(&mappedSubResource, 0, sizeof(mappedSubResource));

		Debug::logErrorCode(context->Map(constBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource));

		//copy new data
		memcpy(mappedSubResource.pData, &mat, sizeof(mat));

		//cleanup
		context->Unmap(constBuffer.Get(), 0);
	}

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
	return matrix;
}

Vec3 Entity::Transform::foreward()
{
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);

	DirectX::XMVECTOR out = DirectX::XMVector3Transform(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotMat);

	return Vec3(DirectX::XMVectorGetX(out), DirectX::XMVectorGetY(out), DirectX::XMVectorGetZ(out));
}

Vec3 Entity::Transform::right()
{
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);

	DirectX::XMVECTOR out = DirectX::XMVector3Transform(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), rotMat);

	return Vec3(DirectX::XMVectorGetX(out), DirectX::XMVectorGetY(out), DirectX::XMVectorGetZ(out));
}

Vec3 Entity::Transform::up()
{
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);

	DirectX::XMVECTOR out = DirectX::XMVector3Transform(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotMat);

	return Vec3(DirectX::XMVectorGetX(out), DirectX::XMVectorGetY(out), DirectX::XMVectorGetZ(out));
}

//position
void Entity::Transform::setPosition(Vec3 position) {
	this->position = position;
}

void Entity::Transform::setPosition(float x, float y, float z) {
	this->position = Vec3(x, y, z);
}

void Entity::Transform::Translate(Vec3 offset)
{
	this->position += (right() * offset.x) + (up() * offset.y) + (foreward() * offset.z);
}

void Entity::Transform::Translate(float x, float y, float z)
{
	this->position += (right() * x) + (up() * y) + (foreward() * z);
}

Vec3 Entity::Transform::getPosition() {
	return position;
}

//rotation
void Entity::Transform::setRotation(Vec3 rotation) {
	this->rotation = rotation;
}

void Entity::Transform::setRotation(float x, float y, float z) {
	this->rotation = Vec3(x, y, z);
}

void Entity::Transform::Rotate(Vec3 offset)
{
	this->rotation += offset;
}

void Entity::Transform::Rotate(float x, float y, float z)
{
	this->rotation += Vec3(x, y, z);
}

Vec3 Entity::Transform::getRotation() {
	return rotation;
}

//scale
void Entity::Transform::setScale(Vec3 scale) {
	this->scale = scale;
}

void Entity::Transform::setScale(float x, float y, float z) {
	this->scale = Vec3(x, y, z);
}

void Entity::Transform::setScale(float scale) {
	this->scale = Vec3(scale, scale, scale);
}

void Entity::Transform::Scale(Vec3 scale)
{
	this->scale *= scale;
}

void Entity::Transform::Scale(float x, float y, float z)
{
	this->scale *= Vec3(x, y, z);
}

void Entity::Transform::Scale(float scale)
{
	this->scale *= scale;
}

Vec3 Entity::Transform::getScale() {
	return scale;
}
