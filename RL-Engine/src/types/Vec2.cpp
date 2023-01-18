#include "../../include/types/Vec2.h"

using namespace Engine;

Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(float value) {
	x = value;
	y = value;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Engine::Vec2::Vec2(Core::Vec2 vec2)
{
	this->x = vec2.x;
	this->y = vec2.y;
}

//functions
float Vec2::distance(Vec2^ a, Vec2^ b) {
	float Out = 0;
	Out += pow(a->x - b->x, 2);
	Out += pow(a->y - b->y, 2);
	return sqrt(Out);
}

Core::Vec2 Vec2::getCoreFormat() {
	return Core::Vec2(x, y);
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
}

void Vec2::operator+=(float other)
{
	this->x += other;
	this->y += other;
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
}

void Vec2::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
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
}

void Vec2::operator*=(float other)
{
	this->x *= other;
	this->y *= other;
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
}

void Vec2::operator/=(float other)
{
	this->x /= other;
	this->y /= other;
}