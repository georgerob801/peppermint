#include <peppermint-preview/classes/game/components/Camera.h>

#include <peppermint-preview/classes/game/GameObject.h>

using namespace peppermint::game;
using namespace peppermint::game::components;
using namespace glm;

Camera::Camera() {
	this->worldUp = vec3(0.0f, 1.0f, 0.0f);
	this->type = Component::CAMERA;
}

#include <format>
#include <peppermint-preview/managers/LogManager.h>

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

vector<byte> Camera::serialise() {
	vector<byte> out;

	unsigned int e = this->type;
	byte* toAdd = (byte*)reinterpret_cast<char*>(&e);

	for (unsigned int i = 0; i < sizeof(unsigned int) / sizeof(byte); i++) {
		out.push_back(toAdd[i]);
	}

	void* id = this;
	byte* toAdd2 = (byte*)reinterpret_cast<char*>(&id);

	for (unsigned int i = 0; i < sizeof(id) / sizeof(byte); i++) {
		out.push_back(toAdd2[i]);
	}

	vector<byte*> thingsToAdd;

	float viewScale = this->viewScale;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&viewScale));

	for (unsigned int i = 0; i < thingsToAdd.size(); i++) {
		for (unsigned int j = 0; j < sizeof(float) / sizeof(byte); j++) {
			out.push_back(thingsToAdd[i][j]);
		}
	}

	//out += "Component:\n";
	//out += "Type: Camera\n";
	//out += std::format("ID: {}\n", (void*)this);
	//out += "Data:\n";
	//out += std::format("ViewScale: {}\n", this->viewScale);

	return out;
}

void Camera::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	this->viewScale = *reinterpret_cast<float*>(&bytes[position]);

	this->deserialisedSize = sizeof(void*) + sizeof(float);
}