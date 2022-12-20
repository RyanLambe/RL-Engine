#include "../../include/types/Vec3.h"

Vec3::Vec3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vec3::Vec3(float value) {
	this->x = value;
	this->y = value;
	this->z = value;
}

Vec3::Vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3Struct* Vec3::getStruct() {
	str.x = x;
	str.y = y;
	str.z = z;
	return &str;
}

float Vec3::distance(Vec3 a, Vec3 b) {
	float Out = 0;
	Out += pow(a.x - b.x, 2);
	Out += pow(a.y - b.y, 2);
	Out += pow(a.z - b.z, 2);
	return sqrt(Out);
}
