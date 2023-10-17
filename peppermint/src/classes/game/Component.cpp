#include <peppermint/classes/game/Component.h>

using namespace peppermint::game;

void Component::start() {}
void Component::awake() {}
void Component::loop() {}

Component* Component::setGameObject(void* gameObject) {
	this->gameObject = gameObject;
	return this;
}

void* Component::getGameObject() {
	return this->gameObject;
}