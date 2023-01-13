#include "../include/Time.h"

float Engine::Time::getTime() {
	return Core::Time::getTime();
}

float Engine::Time::deltaTime() {
	return Core::Time::deltaTime();
}