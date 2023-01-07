#include "../../pch.h"
#include "../../include/types/Vec2.h"

using namespace Engine;

Vec2::Vec2() : Managed(new Core::Vec2()) {
	x = 0;
	y = 0;
}

Vec2::Vec2(float value) : Managed(new Core::Vec2(value)) {
	x = value;
	y = value;
}

Vec2::Vec2(float x, float y) : Managed(new Core::Vec2(x, y)) {
	this->x = x;
	this->y = y;
}

//functions
float Vec2::distance(Vec2^ a, Vec2^ b) {
	float Out = 0;
	Out += pow(a->x - b->x, 2);
	Out += pow(a->y - b->y, 2);
	return sqrt(Out);
}

//addition
Vec2^ Vec2::operator+(Vec2^ other)
{
	return gcnew Vec2(this->x + other->x, this->y + other->y);
}

Vec2^ Vec2::operator+(float other)
{
	return gcnew Vec2(this->x + other, this->y + other);
}

void Vec2::operator+=(Vec2^ other)
{
	this->x += other->x;
	this->y += other->y;
	instance->operator+=(*other->instance);
}

void Vec2::operator+=(float other)
{
	this->x += other;
	this->y += other;
	instance->operator+=(other);
}

//subtraction
Vec2^ Vec2::operator-(Vec2^ other)
{
	return gcnew Vec2(this->x - other->x, this->y - other->y);
}

Vec2^ Vec2::operator-(float other)
{
	return gcnew Vec2(this->x - other, this->y - other);
}

void Vec2::operator-=(Vec2^ other)
{
	this->x -= other->x;
	this->y -= other->y;
	instance->operator-=(*other->instance);
}

void Vec2::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
	instance->operator-=(other);
}

//multiplication
Vec2^ Vec2::operator*(Vec2^ other)
{
	return gcnew Vec2(this->x * other->x, this->y * other->y);
}

Vec2^ Vec2::operator*(float other)
{
	return gcnew Vec2(this->x * other, this->y * other);
}

void Vec2::operator*=(Vec2^ other)
{
	this->x *= other->x;
	this->y *= other->y;
	instance->operator*=(*other->instance);
}

void Vec2::operator*=(float other)
{
	this->x *= other;
	this->y *= other;
	instance->operator*=(other);
}

//division
Vec2^ Vec2::operator/(Vec2^ other)
{
	return gcnew Vec2(this->x / other->x, this->y / other->y);
}

Vec2^ Vec2::operator/(float other)
{
	return gcnew Vec2(this->x / other, this->y / other);
}

void Vec2::operator/=(Vec2^ other)
{
	this->x /= other->x;
	this->y /= other->y;
	instance->operator/=(*other->instance);
}

void Vec2::operator/=(float other)
{
	this->x /= other;
	this->y /= other;
	instance->operator/=(other);
}