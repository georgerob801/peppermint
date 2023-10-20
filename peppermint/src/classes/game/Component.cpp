#include <peppermint/classes/game/Component.h>

using namespace peppermint::game;

void Component::start() {}
void Component::awake() {}
void Component::loop() {}

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

void Component::enable() {
	this->enabled = true;
}

void Component::disable() {
	this->enabled = false;
}

bool Component::isEnabled() {
	return this->enabled;
}