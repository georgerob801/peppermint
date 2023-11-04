#include <peppermint/classes/game/components/Transform.h>

#include <glm/gtx/quaternion.hpp>
#include <format>

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

#include <iostream>

vector<byte> Transform::serialise() {
	vector<byte> out;

	unsigned int e = this->type;
	byte* toAdd = (byte*)reinterpret_cast<char*>(&e);

	for (unsigned int i = 0; i < sizeof(unsigned int) / sizeof(byte); i++) {
		out.push_back(toAdd[i]);
	}

	vector<byte*> thingsToAdd;

	void* id = this;
	byte* toAdd2 = (byte*)reinterpret_cast<char*>(&id);

	for (unsigned int i = 0; i < sizeof(id) / sizeof(byte); i++) {
		out.push_back(toAdd2[i]);
	}

	float xPos = this->position.x;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&xPos));
	float yPos = this->position.x;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&yPos));
	float zPos = this->position.x;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&zPos));

	float xRot = this->rotation.x;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&xRot));
	float yRot = this->rotation.x;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&yRot));
	float zRot = this->rotation.x;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&zRot));

	float xSca = this->scale.x;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&xSca));
	float ySca = this->scale.x;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&ySca));
	float zSca = this->scale.x;
	thingsToAdd.push_back(reinterpret_cast<byte*>(&zSca));

	for (unsigned int i = 0; i < thingsToAdd.size(); i++) {
		for (unsigned int j = 0; j < sizeof(float) / sizeof(byte); j++) {
			out.push_back(thingsToAdd[i][j]);
		}
	}

	//out += "Component:\n";
	//out += "Type: Transform\n";
	//out += std::format("ID: {}\n", (void*)this);
	//out += "Data:\n";
	//out += "Position:\n";
	//out += std::format("X: {}\n", this->position.x);
	//out += std::format("Y: {}\n", this->position.y);
	//out += std::format("Z: {}\n", this->position.z);
	//out += "Rotation:\n";
	//out += std::format("X: {}\n", this->rotation.x);
	//out += std::format("Y: {}\n", this->rotation.y);
	//out += std::format("Z: {}\n", this->rotation.z);
	//out += "Scale:\n";
	//out += std::format("X: {}\n", this->scale.x);
	//out += std::format("Y: {}\n", this->scale.y);
	//out += std::format("Z: {}\n", this->scale.z);

	return out;
}

void Transform::deserialise(vector<byte> bytes) {

}