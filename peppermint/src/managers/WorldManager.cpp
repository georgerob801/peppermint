#include <peppermint/managers/WorldManager.h>

using namespace peppermint::managers;

void WorldManager::start() {
	// this will be exponentially more laggy and will require refactoring
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < this->gameObjects[i].components.size(); j++) {
			if (this->gameObjects[i].components[j]->isEnabled()) {
				this->gameObjects[i].components[j]->start();
			}
		}
	}
}

void WorldManager::loop() {
	// this will also be exponentially more laggy but worse
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < this->gameObjects[i].components.size(); j++) {
			this->gameObjects[i].components[j]->loop();
		}
	}
}