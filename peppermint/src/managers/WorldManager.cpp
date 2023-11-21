#include <peppermint/managers/WorldManager.h>
#include <type_traits>

#include <peppermint/classes/game/components/renderers/Renderer.h>
#include <peppermint/classes/rendering/RenderStack.h>

#include <peppermint/classes/rendering/TilesetAnimationStateInfomation.hpp>

#include <peppermint/Exceptions.hpp>

#include <peppermint/classes/game/components/NavigableMap.hpp>
#include <peppermint/classes/game/components/PlayerController.h>
#include <peppermint/classes/game/components/renderers/BasicPlayerRenderer.h>
#include <peppermint/classes/game/components/renderers/AnimatedTilesetRenderer.h>

#include <algorithm>
#include <iostream>
#include <fstream>

using namespace peppermint::managers;

WorldManager::WorldManager() {
	this->filePath = new Asset(Asset::PPMINT_WORLD_FILE);
	this->filePath->path = (char*)"";
}

WorldManager::WorldManager(char* filePath) {
	this->filePath = new Asset(Asset::PPMINT_WORLD_FILE);
	this->filePath->path = filePath;
}

// only runs once so not as painfully laggy
void WorldManager::awake() {
	this->stopProcessingWorld = false;
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
			if (this->gameObjects[i]->components[j]->isEnabled() && !this->gameObjects[i]->components[j]->isInitialised()) {
				this->gameObjects[i]->components[j]->start();
				this->gameObjects[i]->components[j]->initialise();
			}
		}
	}
}

// this will also be exponentially more laggy but worse
void WorldManager::loop(Window* window) {
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		if (this->stopProcessingWorld) break;
		for (unsigned int j = 0; j < this->gameObjects[i]->components.size(); j++) {
			if (this->stopProcessingWorld) break;
			this->gameObjects[i]->components[j]->loop();
			if (this->stopProcessingWorld) break;

			if (Renderer* rendererComponent = dynamic_cast<Renderer*>(this->gameObjects[i]->components[j])) {
				peppermint::rendering::RenderItem renderItem;

				if (TilesetAnimationStateInformation* tilesetAnimationRendererComponent = dynamic_cast<TilesetAnimationStateInformation*>(rendererComponent)) {
					renderItem = {
						.shader = shader,
						.go = this->gameObjects[i],
						.mesh = rendererComponent->getOrGenerateMesh(),
						.uvOffset = tilesetAnimationRendererComponent->getUVOffset(),
						.textureToUse = tilesetAnimationRendererComponent->getTexOffset(),
						.fromWorld = this
					};
				} else {
					renderItem = {
						.shader = shader,
						.go = this->gameObjects[i],
						.mesh = rendererComponent->getOrGenerateMesh(),
						.fromWorld = this
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

void WorldManager::initialiseFromWorldFile() {
	// cout << "would initialise from " << this->filePath->path << " here" << endl;
	this->initialised = false;
	this->loadWorldFile(this->filePath->path);
	this->initialised = true;
}

void WorldManager::setWorldFileAsset(Asset* item) {
	this->filePath = item;
}

void WorldManager::unload() {
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		delete this->gameObjects[i];
	}
	this->stopProcessingWorld = true;
	this->initialised = false;
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

void WorldManager::loadWorldFile(const char* filename) {
	this->loadWorldFile((char*)filename);
}

void WorldManager::loadWorldFile(char* filename) {
	std::ifstream worldFile(filename, std::ios::binary | std::ios::in);
	worldFile.unsetf(std::ios::skipws);

	std::streampos fileSize;

	worldFile.seekg(0, std::ios::end);
	fileSize = worldFile.tellg();
	worldFile.seekg(0, std::ios::beg);

	std::vector<unsigned char> chars;
	chars.reserve(fileSize);

	chars.insert(chars.begin(), std::istream_iterator<unsigned char>(worldFile), std::istream_iterator<unsigned char>());

	std::vector<byte> allBytes;
	allBytes.reserve(fileSize);
	for (unsigned int i = 0; i < chars.size(); i++) {
		allBytes.push_back((byte)chars[i]);
	}

	this->deserialise(allBytes);
}

void WorldManager::deserialise(vector<byte> bytes) {
	if (bytes.size() < 16) {
		throw peppermint::exceptions::serialisation::world::CorruptedFileException();
	}

	if (bytes[0x00] != (byte)0x01) {
		throw peppermint::exceptions::serialisation::world::InvalidFileTypeException();
	}

	// delete game objects
	this->gameObjects.clear();
	// free memory
	vector<GameObject*>().swap(this->gameObjects);

	unsigned long long position = 0x10;
	unsigned int numGameObjects = *reinterpret_cast<unsigned int*>(&bytes[position]);

	position += sizeof(unsigned int);

	for (unsigned int i = 0; i < numGameObjects; i++) {
		GameObject* go = this->createGameObject();
		unsigned int numComponents = *reinterpret_cast<unsigned int*>(&bytes[position]);
		unsigned long long gameObjectLength = sizeof(unsigned int) + sizeof(void*) + (numComponents * sizeof(void*));

		vector<byte> subVector(gameObjectLength);
		copy(bytes.begin() + position, bytes.begin() + position + gameObjectLength, subVector.begin());

		go->deserialise(subVector);

		position += gameObjectLength;
	}

	// component time
	vector<Component*> componentsToMatch;

	unsigned int numComponents = *reinterpret_cast<unsigned int*>(&bytes[position]);
	componentsToMatch.reserve(numComponents);
	position += sizeof(unsigned int);
	
	for (unsigned int i = 0; i < numComponents; i++) {
		Component::ComponentType coType = (Component::ComponentType)(*reinterpret_cast<unsigned int*>(&bytes[position]));
		position += sizeof(unsigned int);

		Component* co;
		vector<byte> subVector(bytes.size() - position);

		switch (coType) {
		case Component::TRANSFORM:
			co = new Transform();
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			co->deserialise(subVector);

			break;
		case Component::CAMERA:
			co = new Camera();
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			co->deserialise(subVector);
			break;
		case Component::NAVIGABLE_MAP:
			co = new NavigableMap(*reinterpret_cast<unsigned int*>(&bytes[position + sizeof(void*)]), *reinterpret_cast<unsigned int*>(&bytes[position + sizeof(void*) + sizeof(unsigned int)]));
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			co->deserialise(subVector);
			break;
		case Component::PLAYER_CONTROLLER:
			co = new PlayerController();
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			co->deserialise(subVector);
			break;
		case Component::BASIC_PLAYER_RENDERER:
			co = new BasicPlayerRenderer(*reinterpret_cast<unsigned int*>(&bytes[position + sizeof(void*)]), *reinterpret_cast<unsigned int*>(&bytes[position + sizeof(void*) + sizeof(unsigned int)]));
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			co->deserialise(subVector);
			break;
		case Component::TILESET_RENDERER:
			co = new TilesetRenderer(*reinterpret_cast<unsigned int*>(&bytes[position + sizeof(void*) + sizeof(void*)]), *reinterpret_cast<unsigned int*>(&bytes[position + sizeof(void*) + sizeof(void*) + sizeof(unsigned int)]));
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			co->deserialise(subVector);
			break;
		case Component::ANIMATED_TILESET_RENDERER:
			co = new AnimatedTilesetRenderer(*reinterpret_cast<unsigned int*>(&bytes[position + sizeof(void*) + sizeof(void*)]), *reinterpret_cast<unsigned int*>(&bytes[position + sizeof(void*) + sizeof(void*) + sizeof(unsigned int)]));
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			co->deserialise(subVector);
			break;
		case Component::WARP_TILE:
			co = new WarpTile();
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			co->deserialise(subVector);
			break;
		default:
			throw peppermint::exceptions::serialisation::world::CorruptedFileException();
		}

		componentsToMatch.push_back(co);
		position += co->getDeserialisedSize();
	}

	// pass over to join components to gameobjects
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < this->gameObjects[i]->relatedSerialisedIDs.size(); j++) {
			void* lookingFor = this->gameObjects[i]->relatedSerialisedIDs[j];

			vector<Component*>::iterator comp = find_if(componentsToMatch.begin(), componentsToMatch.end(), [lookingFor](Component* item) { return item->serialisedID == lookingFor; });

			if (comp == componentsToMatch.end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

			/*this->gameObjects[i]->components.push_back(*comp);

			(*comp)->setGameObject((void*)this->gameObjects[i]);*/

			this->gameObjects[i]->addComponent(*comp);

			if ((*comp)->getType() == Component::TRANSFORM) {
				this->gameObjects[i]->transform = (Transform*)(*comp);
			}
		}
	}

	// pass over to setup links
	for (unsigned int i = 0; i < componentsToMatch.size(); i++) {
		switch (componentsToMatch[i]->getType()) {
		case Component::TRANSFORM:
		{
			Transform* tra = (Transform*)componentsToMatch[i];
			if (tra->relatedSerialisedIDs.size() > 0) {
				void* toFind = tra->relatedSerialisedIDs[0];
				vector<Component*>::iterator index = find_if(componentsToMatch.begin(), componentsToMatch.end(), [toFind](Component* item) { return item->serialisedID == toFind; });

				if (index == componentsToMatch.end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

				tra->parent = (Transform*)(*index);
			}
			break;
		}
		case Component::PLAYER_CONTROLLER:
		{
			PlayerController* pc = (PlayerController*)componentsToMatch[i];
			void* toFind = pc->relatedSerialisedIDs[0];

			vector<Component*>::iterator index = find_if(componentsToMatch.begin(), componentsToMatch.end(), [toFind](Component* item) { return item->serialisedID == toFind; });

			if (index == componentsToMatch.end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

			pc->navMap = (NavigableMap*)(*index);
			break;
		}
		case Component::BASIC_PLAYER_RENDERER:
		{
			BasicPlayerRenderer* bpr = (BasicPlayerRenderer*)componentsToMatch[i];
			void* toFind = bpr->relatedSerialisedIDs[0];

			vector<Component*>::iterator index = find_if(componentsToMatch.begin(), componentsToMatch.end(), [toFind](Component* item) { return item->serialisedID == toFind; });

			if (index == componentsToMatch.end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

			bpr->pc = (PlayerController*)(*index);



			toFind = bpr->relatedSerialisedIDs[1];
			vector<Asset*>::iterator tilesetIndex = find_if(this->assets->begin(), this->assets->end(), [toFind](Asset* item) { return item->serialisedID == toFind; });
			if (tilesetIndex == this->assets->end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

			bpr->tileset = (Tileset*)(*tilesetIndex);

			vector<TilesetAnimation*> anims;

			for (unsigned int j = 2; j < bpr->relatedSerialisedIDs.size(); j++) {
				void* toFindA = bpr->relatedSerialisedIDs[j];

				vector<Asset*>::iterator indexA = find_if(this->assets->begin(), this->assets->end(), [toFindA](Asset* item) { return item->serialisedID == toFindA; });
				if (indexA == this->assets->end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

				anims.push_back((TilesetAnimation*)(*indexA));
			}

			bpr->up = anims[0];
			bpr->down = anims[1];
			bpr->left = anims[2];
			bpr->right = anims[3];

			bpr->generateTextures();
			bpr->generateVertices();

			break;
		}
		case Component::TILESET_RENDERER:
		{
			TilesetRenderer* tr = (TilesetRenderer*)componentsToMatch[i];
			void* toFind = tr->relatedSerialisedIDs[0];

			vector<Asset*>::iterator index = find_if(this->assets->begin(), this->assets->end(), [toFind](Asset* item) { return item->serialisedID == toFind; });
			if (index == this->assets->end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

			tr->tileset = (Tileset*)(*index);

			tr->generateTextures();
			tr->generateVertices();

			break;
		}
		case Component::ANIMATED_TILESET_RENDERER:
		{
			AnimatedTilesetRenderer* atr = (AnimatedTilesetRenderer*)componentsToMatch[i];
			void* toFind = atr->relatedSerialisedIDs[0];

			vector<Asset*>::iterator index = find_if(this->assets->begin(), this->assets->end(), [toFind](Asset* item) { return item->serialisedID == toFind; });
			if (index == this->assets->end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

			atr->tileset = (Tileset*)(*index);

			for (unsigned int j = 1; j < atr->relatedSerialisedIDs.size(); j++) {
				void* assetToFind = atr->relatedSerialisedIDs[j];

				vector<Asset*>::iterator index2 = find_if(this->assets->begin(), this->assets->end(), [assetToFind](Asset* item) { return item->serialisedID == assetToFind; });
				if (index2 == this->assets->end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

				atr->animations.push_back((TilesetAnimation*)(*index2));
			}
			
			atr->generateTextures();
			atr->generateVertices();

			break;
		}
		case Component::NAVIGABLE_MAP:
		{
			NavigableMap* nvm = (NavigableMap*)componentsToMatch[i];

			for (unsigned int j = 0; j < componentsToMatch[i]->relatedSerialisedIDs.size(); j++) {
				void* toFind = nvm->relatedSerialisedIDs[j];

				vector<Component*>::iterator index = find_if(componentsToMatch.begin(), componentsToMatch.end(), [toFind](Component* item) { return item->serialisedID == toFind; });
				if (index == componentsToMatch.end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

				nvm->warpTiles.push_back((WarpTile*)(*index));
			}

			break;
		}
		default:
			break;
		}
	}
}

Camera* WorldManager::getFirstCamera() {
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < this->gameObjects[i]->components.size(); j++) {
			Camera* test = dynamic_cast<Camera*>(this->gameObjects[i]->components[j]);
			if (test) return test;
		}
	}
	return nullptr;
}