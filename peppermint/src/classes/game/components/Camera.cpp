#include <peppermint/classes/game/components/Camera.h>

#include <peppermint/classes/game/GameObject.h>

using namespace peppermint::game;
using namespace peppermint::game::components;
using namespace glm;

Camera::Camera() {
	this->worldUp = vec3(0.0f, 1.0f, 0.0f);
}

#include <format>
#include <peppermint/managers/LogManager.h>

mat4 Camera::getViewMatrix() {
	vec3 position = ((GameObject*)this->getGameObject())->transform->getGlobalPosition();

	updateCameraVectors();

	return lookAt(position, position + this->front, this->up) * this->viewScale;
}

void Camera::updateCameraVectors() {
	vec3 newFront;

	Transform* transform = ((GameObject*)this->getGameObject())->transform;

	vec3 globalRotation = transform->getGlobalRotation();

	newFront.x = cos(globalRotation.y) * cos(globalRotation.x);
	newFront.y = sin(globalRotation.x);
	newFront.z = sin(globalRotation.y) * cos(globalRotation.x);

	this->front = normalize(newFront);

	this->right = normalize(cross(this->front, this->worldUp));
	this->up = normalize(cross(this->right, this->front));
}