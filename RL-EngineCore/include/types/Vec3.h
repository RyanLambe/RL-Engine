#pragma once

#include <math.h>

class Vec3 {
public:

	//conponents
	float x;
	float y;
	float z;

	//constructors
	Vec3();
	Vec3(float value);
	Vec3(float x, float y, float z);

	//functions
	static float distance(Vec3 a, Vec3 b);

	//operators
	Vec3 operator+(Vec3 other);
	Vec3 operator+(float other);
	void operator+=(Vec3 other);
	void operator+=(float other);

	Vec3 operator-(Vec3 other);
	Vec3 operator-(float other);
	void operator-=(Vec3 other);
	void operator-=(float other);

	Vec3 operator*(Vec3 other);
	Vec3 operator*(float other);
	void operator*=(Vec3 other);
	void operator*=(float other);

	Vec3 operator/(Vec3 other);
	Vec3 operator/(float other);
	void operator/=(Vec3 other);
	void operator/=(float other);

};