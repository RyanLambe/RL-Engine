#pragma once

#include <math.h>

class Vec2 {
public:

	//components
	float x;
	float y;

	//constructors
	Vec2();
	Vec2(float value);
	Vec2(float x, float y);

	//functions
	static float distance(Vec2 a, Vec2 b);

	//operators
	Vec2 operator+(Vec2 other);
	Vec2 operator+(float other);
	void operator+=(Vec2 other);
	void operator+=(float other);

	Vec2 operator-(Vec2 other);
	Vec2 operator-(float other);
	void operator-=(Vec2 other);
	void operator-=(float other);

	Vec2 operator*(Vec2 other);
	Vec2 operator*(float other);
	void operator*=(Vec2 other);
	void operator*=(float other);

	Vec2 operator/(Vec2 other);
	Vec2 operator/(float other);
	void operator/=(Vec2 other);
	void operator/=(float other);

};