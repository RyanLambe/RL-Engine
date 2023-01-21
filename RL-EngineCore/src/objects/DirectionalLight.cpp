#include "../../include/objects/DirectionalLight.h"

Core::DirectionalLight::DirectionalLight(Entity* entity) : Entity::Component(entity) {
	setType("DirectionalLight");
}
