#include "../../include/types/Vec3.h"

// constructors
Core::Vec3::Vec3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Core::Vec3::Vec3(float value) {
	this->x = value;
	this->y = value;
	this->z = value;
}

Core::Vec3::Vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Core::Vec3::Vec3(Core::Vec3* vec)
{
	this->x = vec->x;
	this->y = vec->y;
	this->z = vec->z;
}

//functions
float Core::Vec3::distance(Vec3 a, Vec3 b) {
	float Out = 0;
	Out += pow(a.x - b.x, 2);
	Out += pow(a.y - b.y, 2);
	Out += pow(a.z - b.z, 2);
	return sqrt(Out);
}

//addition
Core::Vec3 Core::Vec3::operator+(Vec3 other)
{
	return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Core::Vec3 Core::Vec3::operator+(float other)
{
	return Vec3(this->x + other, this->y + other, this->z + other);
}

void Core::Vec3::operator+=(Vec3 other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

void Core::Vec3::operator+=(float other)
{
	this->x += other;
	this->y += other;
	this->z += other;
}

//subtraction
Core::Vec3 Core::Vec3::operator-(Vec3 other)
{
	return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Core::Vec3 Core::Vec3::operator-(float other)
{
	return Vec3(this->x - other, this->y - other, this->z - other);
}

void Core::Vec3::operator-=(Vec3 other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
}

void Core::Vec3::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;
}

//multiplication
Core::Vec3 Core::Vec3::operator*(Vec3 other)
{
	return Vec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

Core::Vec3 Core::Vec3::operator*(float other)
{
	return Vec3(this->x * other, this->y * other, this->z * other);
}

void Core::Vec3::operator*=(Vec3 other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
}

void Core::Vec3::operator*=(float other)
{
	this->x *= other;
	this->y *= other;
	this->z *= other;
}

//division
Core::Vec3 Core::Vec3::operator/(Vec3 other)
{
	return Vec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

Core::Vec3 Core::Vec3::operator/(float other)
{
	return Vec3(this->x / other, this->y / other, this->z / other);
}

void Core::Vec3::operator/=(Vec3 other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
}

void Core::Vec3::operator/=(float other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;
}
