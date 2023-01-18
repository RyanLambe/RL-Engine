#include "../../include/types/Transform.h"

using namespace Engine;

Engine::Transform::Transform(Core::Transform* transform)
{
	instance = transform;
}

Core::Transform* Transform::getCoreFormat() {
	return instance;
}

Vec3^ Transform::foreward() {
	Core::Vec3 temp = instance->foreward();
	return gcnew Vec3(temp.x, temp.y, temp.z);
}

Vec3^ Transform::right() {
	Core::Vec3 temp = instance->right();
	return gcnew Vec3(temp.x, temp.y, temp.z);
}

Vec3^ Transform::up() {
	Core::Vec3 temp = instance->up();
	return gcnew Vec3(temp.x, temp.y, temp.z);
}

//position
void Transform::setPosition(Vec3^ position) { 
	instance->setPosition(position->getCoreFormat());
}
void Transform::setPosition(float x, float y, float z) {
	instance->setPosition(x, y, z);
}
void Transform::Translate(Vec3^ offset) {
	instance->Translate(offset->getCoreFormat());
}
void Transform::Translate(float x, float y, float z) {
	instance->Translate(x, y, z);
}
Vec3^ Transform::getPosition() {
	return gcnew Vec3(instance->getPosition());
}

//rotation
void Transform::setRotation(Vec3^ rotation) {
	instance->setRotation(rotation->getCoreFormat());
}
void Transform::setRotation(float x, float y, float z) {
	instance->setRotation(x, y, z);
}
void Transform::Rotate(Vec3^ offset) {
	instance->Rotate(offset->getCoreFormat());
}
void Transform::Rotate(float x, float y, float z) {
	instance->Rotate(x, y, z);
}
Vec3^ Transform::getRotation() {
	return gcnew Vec3(instance->getRotation());
}

//scale
void Transform::setScale(Vec3^ scale) { 
	instance->setScale(scale->getCoreFormat());
}
void Transform::setScale(float x, float y, float z) { 
	instance->setScale(x, y, z);
}
void Transform::setScale(float scale) { 
	instance->setScale(scale, scale, scale);
}
void Transform::Scale(Vec3^ scale) { 
	instance->Scale(scale->getCoreFormat());
}
void Transform::Scale(float x, float y, float z) { 
	instance->Scale(x, y, z);
}
void Transform::Scale(float scale) { 
	instance->Scale(scale, scale, scale);
}
Vec3^ Transform::getScale() { 
	return gcnew Vec3(instance->getScale());
}