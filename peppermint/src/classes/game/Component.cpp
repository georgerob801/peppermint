#include <peppermint/classes/game/Component.h>

#include <format>

using namespace peppermint::game;

#include <iostream>
Component::~Component() { }

void Component::start() { }
void Component::awake() { }
void Component::loop() { }

void Component::initialise() {
	this->initialised = true;
}

bool Component::isInitialised() {
	return this->initialised;
}

Component* Component::setGameObject(void* gameObject) {
	this->gameObject = gameObject;
	return this;
}

void* Component::getGameObject() {
	return this->gameObject;
}

vector<byte> Component::serialise() {
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

	//out += "Component:\n";
	//out += std::format("ID: {}\n", (void*)this);

	return out;
}

void Component::deserialise(vector<byte> bytes) {

}

unsigned int Component::getType() {
	return this->type;
}