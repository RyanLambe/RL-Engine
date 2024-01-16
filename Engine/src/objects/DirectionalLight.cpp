#include "DirectionalLight.h"

using namespace rl;

DirectionalLight::DirectionalLight(Entity* entity) : Entity::Component(entity) {
	setType("DirectionalLight");
}
