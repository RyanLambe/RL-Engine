#include "../../include/types/Vec3.h"

using namespace Engine;

Vec3::Vec3() {
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(float value) {
	x = value;
	y = value;
	z = value;
}

Vec3::Vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3(Core::Vec3 vec3) {
	this->x = vec3.x;
	this->y = vec3.y;
	this->z = vec3.z;
}

//functions
float Vec3::distance(Vec3^ a, Vec3^ b) {
	float Out = 0;
	Out += pow(a->x - b->x, 2);
	Out += pow(a->y - b->y, 2);
	Out += pow(a->z - b->z, 2);
	return sqrt(Out);
}

Core::Vec3 Vec3::getCoreFormat() {
	return Core::Vec3(x, y, z);
}

//addition
Vec3^ Vec3::operator+(Vec3^ left, Vec3^ right) {
	return gcnew Vec3(left->x + right->x, left->y + right->y, left->z + right->z);
}

Vec3^ Vec3::operator+(Vec3^ left, float right)
{
	return gcnew Vec3(left->x + right, left->y + right, left->z + right);
}

Vec3^ Vec3::operator+(float left, Vec3^ right)
{
	return gcnew Vec3(left + right->x, left + right->y, left + right->z);
}

void Vec3::operator+=(Vec3^ left, Vec3^ right)
{
	left->x += right->x;
	left->y += right->y;
	left->z += right->z;
}

void Vec3::operator+=(Vec3^ left, float right)
{
	left->x += right;
	left->y += right;
	left->z += right;
}

//subtraction
Vec3^ Vec3::operator-(Vec3^ left, Vec3^ right)
{
	return gcnew Vec3(left->x - right->x, left->y - right->y, left->z - right->z);
}

Vec3^ Vec3::operator-(Vec3^ left, float right)
{
	return gcnew Vec3(left->x - right, left->y - right, left->z - right);
}

Vec3^ Vec3::operator-(float left, Vec3^ right)
{
	return gcnew Vec3(left - right->x, left - right->y, left - right->z);
}

Vec3^ Vec3::operator-(Vec3^ vec) {
	return gcnew Vec3(-vec->x, -vec->y, -vec->z);
}

void Vec3::operator-=(Vec3^ left, Vec3^ right)
{
	left->x -= right->x;
	left->y -= right->y;
	left->z -= right->z;
}

void Vec3::operator-=(Vec3^ left, float right)
{
	left->x -= right;
	left->y -= right;
	left->z -= right;
}

//multiplication
Vec3^ Vec3::operator*(Vec3^ left, Vec3^ right)
{
	return gcnew Vec3(left->x * right->x, left->y * right->y, left->z * right->z);
}

Vec3^ Vec3::operator*(Vec3^ left, float right)
{
	return gcnew Vec3(left->x * right, left->y * right, left->z * right);
}

Vec3^ Vec3::operator*(float left, Vec3^ right)
{
	return gcnew Vec3(left * right->x, left * right->y, left * right->z);
}

void Vec3::operator*=(Vec3^ left, Vec3^ right)
{
	left->x *= right->x;
	left->y *= right->y;
	left->z *= right->z;
}

void Vec3::operator*=(Vec3^ left, float right)
{
	left->x *= right;
	left->y *= right;
	left->z *= right;
}

//division
Vec3^ Vec3::operator/(Vec3^ left, Vec3^ right)
{
	return gcnew Vec3(left->x / right->x, left->y / right->y, left->z / right->z);
}

Vec3^ Vec3::operator/(Vec3^ left, float right)
{
	return gcnew Vec3(left->x / right, left->y / right, left->z / right);
}

Vec3^ Vec3::operator/(float left, Vec3^ right)
{
	return gcnew Vec3(left / right->x, left / right->y, left / right->z);
}

void Vec3::operator/=(Vec3^ left, Vec3^ right)
{
	left->x /= right->x;
	left->y /= right->y;
	left->z /= right->z;
}

void Vec3::operator/=(Vec3^ left, float right)
{
	left->x /= right;
	left->y /= right;
	left->z /= right;
}