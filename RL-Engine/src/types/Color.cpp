#include "../../include/types/Color.h"

//constructors
Engine::Color::Color() {
	this->r = 1;
	this->g = 1;
	this->b = 1;
}

Engine::Color::Color(float value) {
	this->r = value;
	this->g = value;
	this->b = value;
}

Engine::Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}