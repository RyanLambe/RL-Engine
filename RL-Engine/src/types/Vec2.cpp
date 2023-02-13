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
//test b
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
Vec2^ Vec2::operator+(Vec2^ left, Vec2^ right)
{
	return gcnew Vec2(left->x + right->x, left->y + right->y);
}

Vec2^ Vec2::operator+(Vec2^ left, float right)
{
	return gcnew Vec2(left->x + right, left->y + right);
}

Vec2^ Vec2::operator+(float left, Vec2^ right)
{
	return gcnew Vec2(left + right->x, left + right->y);
}

void Vec2::operator+=(Vec2^ left, Vec2^ right)
{
	left->x += right->x;
	left->y += right->y;
}

void Vec2::operator+=(Vec2^ left, float right)
{
	left->x += right;
	left->y += right;
}

//subtraction
Vec2^ Vec2::operator-(Vec2^ left, Vec2^ right)
{
	return gcnew Vec2(left->x - right->x, left->y - right->y);
}

Vec2^ Vec2::operator-(Vec2^ left, float right)
{
	return gcnew Vec2(left->x - right, left->y - right);
}

Vec2^ Vec2::operator-(float left, Vec2^ right)
{
	return gcnew Vec2(left - right->x, left - right->y);
}

Vec2^ Vec2::operator-(Vec2^ vec)
{
	return gcnew Vec2(-vec->x, -vec->y);
}

void Vec2::operator-=(Vec2^ left, Vec2^ right)
{
	left->x -= right->x;
	left->y -= right->y;
}

void Vec2::operator-=(Vec2^ left, float right)
{
	left->x -= right;
	left->y -= right;
}

//multiplication
Vec2^ Vec2::operator*(Vec2^ left, Vec2^ right)
{
	return gcnew Vec2(left->x * right->x, left->y * right->y);
}

Vec2^ Vec2::operator*(Vec2^ left, float right)
{
	return gcnew Vec2(left->x * right, left->y * right);
}

Vec2^ Vec2::operator*(float left, Vec2^ right)
{
	return gcnew Vec2(left * right->x, left * right->y);
}

void Vec2::operator*=(Vec2^ left, Vec2^ right)
{
	left->x *= right->x;
	left->y *= right->y;
}

void Vec2::operator*=(Vec2^ left, float right)
{
	left->x *= right;
	left->y *= right;
}

//division
Vec2^ Vec2::operator/(Vec2^ left, Vec2^ right)
{
	return gcnew Vec2(left->x / right->x, left->y / right->y);
}

Vec2^ Vec2::operator/(Vec2^ left, float right)
{
	return gcnew Vec2(left->x / right, left->y / right);
}

Vec2^ Vec2::operator/(float left, Vec2^ right)
{
	return gcnew Vec2(left / right->x, left / right->y);
}

void Vec2::operator/=(Vec2^ left, Vec2^ right)
{
	left->x /= right->x;
	left->y /= right->y;
}

void Vec2::operator/=(Vec2^ left, float right)
{
	left->x /= right;
	left->y /= right;
}