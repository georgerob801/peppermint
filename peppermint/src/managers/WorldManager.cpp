#include <peppermint/managers/WorldManager.h>
#include <type_traits>

#include <peppermint/classes/game/components/renderers/Renderer.h>
#include <peppermint/classes/rendering/RenderStack.h>

#include <peppermint/classes/rendering/TilesetAnimationStateInfomation.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>

using namespace peppermint::managers;

// only runs once so not as painfully laggy
void WorldManager::awake() {
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < this->gameObjects[i]->components.size(); j++) {
			this->gameObjects[i]->components[j]->awake();
		}
	}

	this->sortByZ();
}

void WorldManager::sortByZ() {
	std::sort(this->gameObjects.begin(), this->gameObjects.end(), [](GameObject* go1, GameObject* go2) {
		return go1->transform->getGlobalPosition().z < go2->transform->getGlobalPosition().z;
	});
}

// this will be exponentially more laggy and will require refactoring
void WorldManager::start() {
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < this->gameObjects[i]->components.size(); j++) {
			if (this->gameObjects[i]->components[j]->isEnabled()) {
				this->gameObjects[i]->components[j]->start();
			}
		}
	}
}

// this will also be exponentially more laggy but worse
void WorldManager::loop(Window* window) {
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < this->gameObjects[i]->components.size(); j++) {
			this->gameObjects[i]->components[j]->loop();

			if (Renderer* rendererComponent = dynamic_cast<Renderer*>(this->gameObjects[i]->components[j])) {
				peppermint::rendering::RenderItem renderItem;

				if (TilesetAnimationStateInformation* tilesetAnimationRendererComponent = dynamic_cast<TilesetAnimationStateInformation*>(rendererComponent)) {
					renderItem = {
						.shader = shader,
						.go = this->gameObjects[i],
						.mesh = rendererComponent->getOrGenerateMesh(),
						.uvOffset = tilesetAnimationRendererComponent->getUVOffset(),
						.textureToUse = tilesetAnimationRendererComponent->getTexOffset()
					};
				} else {
					renderItem = {
						.shader = shader,
						.go = this->gameObjects[i],
						.mesh = rendererComponent->getOrGenerateMesh(),
					};
				}

				window->renderManager->activeRenderStack->renderItems.push_back(renderItem);
			}
		}
	}
}

GameObject* WorldManager::createGameObject() {
	GameObject* go = new GameObject();
	this->gameObjects.push_back(go);

	return go;
}

void WorldManager::saveWorldFile(const char* filename) {
	this->saveWorldFile((char*)filename);
}

void WorldManager::saveWorldFile(char* filename) {
	std::ofstream worldFile(filename, std::ios::binary | std::ios::trunc);

	vector<byte> serialised = this->serialise();

	if (serialised.size() > 0) worldFile.write(reinterpret_cast<const char*>(&serialised[0]), serialised.size());

	worldFile.close();
}

vector<byte> WorldManager::serialise() {
	vector<byte> out;

	// header for file version
	out.push_back((byte)0x01);
	out.push_back((byte)0x00);

	while (out.size() < 16) out.push_back((byte)0x00);

	// number of game objects
	unsigned int objects = this->gameObjects.size();
	byte* objectsBytes = (byte*)static_cast<char*>(static_cast<void*>(&objects));

	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(objectsBytes[i]);
	}

	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		vector<byte> gameObjectSerialised = this->gameObjects[i]->serialise();
		out.insert(out.end(), gameObjectSerialised.begin(), gameObjectSerialised.end());

		//while (out.size() % 16 != 0) out.push_back((byte)0x00);
		//for (unsigned int x = 0; x < 16; x++) out.push_back((byte(0xff)));
		//for (unsigned int x = 0; x < 16; x++) out.push_back((byte(0x00)));
	}

	vector<void*> serialisedComponents;
	vector<void*> countedComponents;
	
	unsigned int size = 0;

	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < this->gameObjects[i]->components.size(); j++) {
			if (find(countedComponents.begin(), countedComponents.end(), this->gameObjects[i]->components[j]) == countedComponents.end()) {
				size++;
				countedComponents.push_back(this->gameObjects[i]->components[j]);
			}
		}
	}
	byte* sizeB = reinterpret_cast<byte*>(&size);

	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(sizeB[i]);
	}

	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < this->gameObjects[i]->components.size(); j++) {
			if (find(serialisedComponents.begin(), serialisedComponents.end(), this->gameObjects[i]->components[j]) == serialisedComponents.end()) {
				vector<byte> componentSerialised = this->gameObjects[i]->components[j]->serialise();
				out.insert(out.end(), componentSerialised.begin(), componentSerialised.end());
				serialisedComponents.push_back(this->gameObjects[i]->components[j]);
			}
		}
	}

	return out;
}

void WorldManager::deserialise(vector<byte> bytes) {

}