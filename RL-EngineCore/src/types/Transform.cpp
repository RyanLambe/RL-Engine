#include "../../include/types/Transform.h"

#ifndef TransformEntity
#define TransformEntity
#include "../../include/objects/Entity.h"
#endif



Core::Transform::~Transform() {
	Debug::log("Deleting transform");

}

Core::Transform::Transform()
{
	entity = nullptr;
	matrix = DirectX::XMMatrixIdentity();
}

Core::Transform::Transform(Entity* entity)
{
	this->entity = entity;
	matrix = DirectX::XMMatrixIdentity();
}

void Core::Transform::UpdateBuffer(SmartPtr<ID3D11Device> device, SmartPtr<ID3D11DeviceContext> context) {

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

DirectX::XMMATRIX Core::Transform::getMatrix() {

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

Core::Vec3 Core::Transform::foreward()
{
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);

	DirectX::XMVECTOR out = DirectX::XMVector3Transform(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotMat);

	return Vec3(DirectX::XMVectorGetX(out), DirectX::XMVectorGetY(out), DirectX::XMVectorGetZ(out));
}

Core::Vec3 Core::Transform::right()
{
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);

	DirectX::XMVECTOR out = DirectX::XMVector3Transform(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), rotMat);

	return Vec3(DirectX::XMVectorGetX(out), DirectX::XMVectorGetY(out), DirectX::XMVectorGetZ(out));
}

Core::Vec3 Core::Transform::up()
{
	DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x * pi / 180.0, rotation.y * pi / 180.0, rotation.z * pi / 180.0);

	DirectX::XMVECTOR out = DirectX::XMVector3Transform(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotMat);

	return Vec3(DirectX::XMVectorGetX(out), DirectX::XMVectorGetY(out), DirectX::XMVectorGetZ(out));
}

//position
void Core::Transform::setPosition(Vec3 position) {
	this->position = position;
}

void Core::Transform::setPosition(float x, float y, float z) {
	this->position = Vec3(x, y, z);
}

void Core::Transform::Translate(Vec3 offset)
{
	this->position += offset;
}

void Core::Transform::Translate(float x, float y, float z)
{
	this->position += new Vec3(x, y, z);
}

Core::Vec3 Core::Transform::getPosition() {
	return position;
}

//rotation
void Core::Transform::setRotation(Vec3 rotation) {
	this->rotation = rotation;
}

void Core::Transform::setRotation(float x, float y, float z) {
	this->rotation = Vec3(x, y, z);
}

void Core::Transform::Rotate(Vec3 offset)
{
	this->rotation += offset;
}

void Core::Transform::Rotate(float x, float y, float z)
{
	this->rotation += Vec3(x, y, z);
}

Core::Vec3 Core::Transform::getRotation() {
	return rotation;
}

//scale
void Core::Transform::setScale(Vec3 scale) {
	this->scale = scale;
}

void Core::Transform::setScale(float x, float y, float z) {
	this->scale = Vec3(x, y, z);
}

void Core::Transform::setScale(float scale) {
	this->scale = Vec3(scale, scale, scale);
}

void Core::Transform::Scale(Vec3 scale)
{
	this->scale *= scale;
}

void Core::Transform::Scale(float x, float y, float z)
{
	this->scale *= Vec3(x, y, z);
}

void Core::Transform::Scale(float scale)
{
	this->scale *= scale;
}

Core::Vec3 Core::Transform::getScale() {
	return scale;
}