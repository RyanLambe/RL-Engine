#include "../../include/types/Vec2.h"

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

float Vec2::distance(Vec2 a, Vec2 b) {
	float Out = 0;
	Out += pow(a.x - b.x, 2);
	Out += pow(a.y - b.y, 2);
	return sqrt(Out);
}
