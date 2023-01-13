#include "../../include/types/Vec3.h"

using namespace Engine;

Vec3::Vec3() : Managed(new Core::Vec3()) {
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(float value) : Managed(new Core::Vec3(value)) {
	x = value;
	y = value;
	z = value;
}

Vec3::Vec3(float x, float y, float z) : Managed(new Core::Vec3(x, y, z)) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3(Core::Vec3* vec3) : Managed(new Core::Vec3(vec3->x, vec3->y, vec3->z)) {
	this->x = vec3->x;
	this->y = vec3->y;
	this->z = vec3->z;
}

//functions
float Vec3::distance(Vec3^ a, Vec3^ b) {
	float Out = 0;
	Out += pow(a->x - b->x, 2);
	Out += pow(a->y - b->y, 2);
	Out += pow(a->z - b->z, 2);
	return sqrt(Out);
}

//addition
Vec3^ Vec3::operator+(Vec3^ other)
{
	return gcnew Vec3(this->x + other->x, this->y + other->y, this->z + other->z);
}

Vec3^ Vec3::operator+(float other)
{
	return gcnew Vec3(this->x + other, this->y + other, this->z + other);
}

void Vec3::operator+=(Vec3^ other)
{
	this->x += other->x;
	this->y += other->y;
	this->z += other->z;
	*instance += *other->instance;
}

void Vec3::operator+=(float other)
{
	this->x += other;
	this->y += other;
	this->z += other;
	*instance += other;
}

//subtraction
Vec3^ Vec3::operator-(Vec3^ other)
{
	return gcnew Vec3(this->x - other->x, this->y - other->y, this->z - other->z);
}

Vec3^ Vec3::operator-(float other)
{
	return gcnew Vec3(this->x - other, this->y - other, this->z - other);
}

void Vec3::operator-=(Vec3^ other)
{
	this->x -= other->x;
	this->y -= other->y;
	this->z -= other->z;
	*instance -= *other->instance;
}

void Vec3::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;
	*instance -= other;
}

//multiplication
Vec3^ Vec3::operator*(Vec3^ other)
{
	return gcnew Vec3(this->x * other->x, this->y * other->y, this->z * other->z);
}

Vec3^ Vec3::operator*(float other)
{
	return gcnew Vec3(this->x * other, this->y * other, this->z * other);
}

void Vec3::operator*=(Vec3^ other)
{
	this->x *= other->x;
	this->y *= other->y;
	this->z *= other->z;
	*instance *= *other->instance;
}

void Vec3::operator*=(float other)
{
	this->x *= other;
	this->y *= other;
	this->z *= other;
	*instance *= other;
}

//division
Vec3^ Vec3::operator/(Vec3^ other)
{
	return gcnew Vec3(this->x / other->x, this->y / other->y, this->z / other->z);
}

Vec3^ Vec3::operator/(float other)
{
	return gcnew Vec3(this->x / other, this->y / other, this->z / other);
}

void Vec3::operator/=(Vec3^ other)
{
	this->x /= other->x;
	this->y /= other->y;
	this->z /= other->z;
	*instance *= *other->instance;
}

void Vec3::operator/=(float other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;
	*instance *= other;
}