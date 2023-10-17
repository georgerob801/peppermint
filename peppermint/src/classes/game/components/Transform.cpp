#include <peppermint/classes/game/components/Transform.h>

using namespace peppermint::game::components;
using namespace glm;

Transform::Transform() {
	this->position = vec3(0.0f, 0.0f, 0.0f);
	this->rotation = quat(1.0f, 0.0f, 0.0f, 0.0f);
	this->scale = vec3(1.0f, 1.0f, 1.0f);
}

vec3 Transform::getEulerAngles() {
	return eulerAngles(this->rotation);
}