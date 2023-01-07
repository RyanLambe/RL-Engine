#include "../../include/types/Transform.h"
#include "../../include/objects/Entity.h"

using namespace Core;

Core::Transform::Transform()
{
	entity = nullptr;
}

Core::Transform::Transform(Entity* entity)
{
	this->entity = entity;
}

void Transform::UpdateBuffer(ID3D11Device* device, ID3D11DeviceContext* context) {

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

		Debug::logErrorCode(device->CreateBuffer(&bufferDesc, &initData, constBuffer.Create()));

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

	context->VSSetConstantBuffers(0, 1, constBuffer.GetAddress());
}

DirectX::XMMATRIX Transform::getMatrix() {

	//reset matrix
	matrix = DirectX::XMMatrixIdentity();

	//local Transformation
	matrix *= DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	//converted to radians
	matrix *= DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);
	matrix *= DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//parent transformation
	if (entity == nullptr)
		return matrix;

	if (entity->getParent() == nullptr)
		return matrix;

	//return
	matrix *= entity->getParent()->transform.getMatrix();
	return matrix;
}

Vec3 Transform::foreward()
{
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);

	DirectX::XMVECTOR out = DirectX::XMVector3Transform(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotMat);

	return Vec3(DirectX::XMVectorGetX(out), DirectX::XMVectorGetY(out), DirectX::XMVectorGetZ(out));
}

Vec3 Transform::right()
{
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);

	DirectX::XMVECTOR out = DirectX::XMVector3Transform(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), rotMat);

	return Vec3(DirectX::XMVectorGetX(out), DirectX::XMVectorGetY(out), DirectX::XMVectorGetZ(out));
}

Vec3 Transform::up()
{
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);

	DirectX::XMVECTOR out = DirectX::XMVector3Transform(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotMat);

	return Vec3(DirectX::XMVectorGetX(out), DirectX::XMVectorGetY(out), DirectX::XMVectorGetZ(out));
}

//position
void Transform::setPosition(Vec3 position) {
	this->position = position;
}

void Transform::setPosition(float x, float y, float z) {
	this->position = Vec3(x, y, z);
}

void Transform::Translate(Vec3 offset)
{
	this->position += (right() * offset.x) + (up() * offset.y) + (foreward() * offset.z);
}

void Transform::Translate(float x, float y, float z)
{
	this->position += (right() * x) + (up() * y) + (foreward() * z);
}

Vec3 Transform::getPosition() {
	return position;
}

//rotation
void Transform::setRotation(Vec3 rotation) {
	this->rotation = rotation;
}

void Transform::setRotation(float x, float y, float z) {
	this->rotation = Vec3(x, y, z);
}

void Transform::Rotate(Vec3 offset)
{
	this->rotation += offset;
}

void Transform::Rotate(float x, float y, float z)
{
	this->rotation += Vec3(x, y, z);
}

Vec3 Transform::getRotation() {
	return rotation;
}

//scale
void Transform::setScale(Vec3 scale) {
	this->scale = scale;
}

void Transform::setScale(float x, float y, float z) {
	this->scale = Vec3(x, y, z);
}

void Transform::setScale(float scale) {
	this->scale = Vec3(scale, scale, scale);
}

void Transform::Scale(Vec3 scale)
{
	this->scale *= scale;
}

void Transform::Scale(float x, float y, float z)
{
	this->scale *= Vec3(x, y, z);
}

void Transform::Scale(float scale)
{
	this->scale *= scale;
}

Vec3 Transform::getScale() {
	return scale;
}