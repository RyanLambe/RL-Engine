#include "../../include/types/Vec2.h"

//constructors
Vec2::Vec2() {
	this->x = 0;
	this->y = 0;
}

Vec2::Vec2(float value) {
	this->x = value;
	this->y = value;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

//functions
float Vec2::distance(Vec2 a, Vec2 b) {
	float Out = 0;
	Out += pow(a.x - b.x, 2);
	Out += pow(a.y - b.y, 2);
	return sqrt(Out);
}

//addition
Vec2 Vec2::operator+(Vec2 other)
{
	return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator+(float other)
{
	return Vec2(this->x + other, this->y + other);
}

void Vec2::operator+=(Vec2 other)
{
	this->x += other.x;
	this->y += other.y;
}

void Vec2::operator+=(float other)
{
	this->x += other;
	this->y += other;
}

//subtraction
Vec2 Vec2::operator-(Vec2 other)
{
	return Vec2(this->x - other.x, this->y - other.y);
}

Vec2 Vec2::operator-(float other)
{
	return Vec2(this->x - other, this->y - other);
}

void Vec2::operator-=(Vec2 other)
{
	this->x -= other.x;
	this->y -= other.y;
}

void Vec2::operator-=(float other)
{
	this->x -= other;
	this->y -= other;
}

//multiplication
Vec2 Vec2::operator*(Vec2 other)
{
	return Vec2(this->x * other.x, this->y * other.y);
}

Vec2 Vec2::operator*(float other)
{
	return Vec2(this->x * other, this->y * other);
}

void Vec2::operator*=(Vec2 other)
{
	this->x *= other.x;
	this->y *= other.y;
}

void Vec2::operator*=(float other)
{
	this->x *= other;
	this->y *= other;
}

//division
Vec2 Vec2::operator/(Vec2 other)
{
	return Vec2(this->x / other.x, this->y / other.y);
}

Vec2 Vec2::operator/(float other)
{
	return Vec2(this->x / other, this->y / other);
}

void Vec2::operator/=(Vec2 other)
{
	this->x /= other.x;
	this->y /= other.y;
}

void Vec2::operator/=(float other)
{
	this->x /= other;
	this->y /= other;
}