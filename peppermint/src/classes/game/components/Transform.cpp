#include <peppermint/classes/game/components/Transform.h>

#include <glm/gtx/quaternion.hpp>

using namespace peppermint::game::components;
using namespace glm;

Transform::Transform() {
	this->position = vec3(0.0f, 0.0f, 0.0f);
	this->rotation = vec3(0.0f, 0.0f, 0.0f);
	this->scale = vec3(1.0f, 1.0f, 1.0f);
	this->parent = nullptr;
}

vec3 Transform::getGlobalScale() {
	if (this->parent != nullptr) {
		vec3 parentScale = this->parent->getGlobalScale();
		return vec3(parentScale.x * this->scale.x, parentScale.y * this->scale.y, parentScale.z * this->scale.z);
	} else {
		return this->scale;
	}
}

vec3 Transform::getGlobalRotation() {
	if (this->parent != nullptr) {
		vec3 parentRotation = this->parent->getGlobalRotation();
		return parentRotation + this->rotation;
	} else {
		return this->rotation;
	}
}

vec3 Transform::getGlobalPosition() {
	if (this->parent != nullptr) {
		vec3 parentPosition = this->parent->getGlobalPosition();
		return parentPosition + this->position;
	} else {
		return this->position;
	}
}

mat4 Transform::getMatrix() {
	vec3 adjustedRotation = this->getGlobalRotation();

	mat4 out = rotate(mat4(1.0f), adjustedRotation.x, vec3(1.0f, 0.0f, 0.0f));
	out = rotate(out, adjustedRotation.y, vec3(0.0f, 1.0f, 0.0f));
	out = rotate(out, adjustedRotation.z, vec3(0.0f, 0.0f, 1.0f));

	out = glm::scale(out, this->getGlobalScale());
	out = glm::translate(out, this->getGlobalPosition());

	return out;
}