#include <peppermint/classes/game/components/Camera.h>

#include <peppermint/classes/game/GameObject.h>

using namespace peppermint::game;
using namespace peppermint::game::components;
using namespace glm;

Camera::Camera(vec3 up) {
	this->worldUp = up;

	updateCameraVectors();
}

mat4 Camera::getViewMatrix() {
	Transform* transform = ((GameObject*)this->getGameObject())->transform;

	return lookAt(transform->position, transform->position + this->front, this->up);
}

void Camera::updateCameraVectors() {
	vec3 newFront;

	Transform* transform = ((GameObject*)this->getGameObject())->transform;

	newFront.x = cos(transform->getEulerAngles().z) * cos(transform->getEulerAngles().y);
	newFront.y = sin(transform->getEulerAngles().y);
	newFront.z = sin(transform->getEulerAngles().z) * cos(transform->getEulerAngles().y);

	this->front = normalize(newFront);

	this->right = normalize(cross(this->front, this->worldUp));
	this->up = normalize(cross(this->right, this->front));
}