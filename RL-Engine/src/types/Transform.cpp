#include "../../pch.h"
#include "../../include/types/Transform.h"

using namespace Engine;

Transform::Transform() : Managed(new Core::Transform()) {
	
}

Transform::Transform(Core::Entity* entity) : Managed(new Core::Transform(entity)) {

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