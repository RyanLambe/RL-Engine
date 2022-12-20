#pragma once

#include <math.h>

class Vec3 {
public:

	struct Vec3Struct {
		float x;
		float y;
		float z;
	};

	float x;
	float y;
	float z;

	Vec3();
	Vec3(float value);
	Vec3(float x, float y, float z);

	Vec3Struct* getStruct();

	static float distance(Vec3 a, Vec3 b);

private:
	Vec3Struct str;
};