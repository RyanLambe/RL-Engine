#include "../../include/types/Vec2.h"

//constructors
Core::Vec2::Vec2() {
	this->x = 0;
	this->y = 0;
}

Core::Vec2::Vec2(float value) {
	this->x = value;
	this->y = value;
}

Core::Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

//functions
float Core::Vec2::distance(Vec2 a, Vec2 b) {
	float Out = 0;
	Out += pow(a.x - b.x, 2);
	Out += pow(a.y - b.y, 2);
	return sqrt(Out);
}

//addition
Core::Vec2 Core::Vec2::operator+(Vec2 other)
{
	return Vec2(this->x + other.x, this->y + other.y);
}

Core::Vec2 Core::Vec2::operator+(float other)
{
	return Vec2(this->x + other, this->y + other);
}

void Core::Vec2::operator+=(Vec2 other)
{
	this->x += other.x;
	this->y += other.y;
}

void Core::Vec2::operator+=(float other)
{
	this->x += other;
	this->y += other;
}

//subtraction
Core::Vec2 Core::Vec2::operator-(Vec2 other)
{
	return Vec2(this->x - other.x, this->y - other.y);
}

Core::Vec2 Core::Vec2::operator-(float other)
{
	return Vec2(this->x - other, this->y - other);
}

void Core::Vec2::operator-=(Vec2 other)
{
	this->x -= other.x;
	this->y -= other.y;
}

void Core::Vec2::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
}

//multiplication
Core::Vec2 Core::Vec2::operator*(Vec2 other)
{
	return Vec2(this->x * other.x, this->y * other.y);
}

Core::Vec2 Core::Vec2::operator*(float other)
{
	return Vec2(this->x * other, this->y * other);
}

void Core::Vec2::operator*=(Vec2 other)
{
	this->x *= other.x;
	this->y *= other.y;
}

void Core::Vec2::operator*=(float other)
{
	this->x *= other;
	this->y *= other;
}

//division
Core::Vec2 Core::Vec2::operator/(Vec2 other)
{
	return Vec2(this->x / other.x, this->y / other.y);
}

Core::Vec2 Core::Vec2::operator/(float other)
{
	return Vec2(this->x / other, this->y / other);
}

void Core::Vec2::operator/=(Vec2 other)
{
	this->x /= other.x;
	this->y /= other.y;
}

void Core::Vec2::operator/=(float other)
{
	this->x /= other;
	this->y /= other;
}