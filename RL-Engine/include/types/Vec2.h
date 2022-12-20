#pragma once

#include <math.h>

class Vec2 {
public:
	float x;
	float y;

	Vec2();
	Vec2(float value);
	Vec2(float x, float y);

	static float distance(Vec2 a, Vec2 b);
};