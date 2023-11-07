#include <iostream>


#include <stb_image/stb_image.h>

#include <peppermint/managers/LogManager.h>

#include <peppermint/managers/EngineManager.h>

using namespace std;
using namespace glm;

using namespace peppermint;
using namespace peppermint::managers;

#include <peppermint/classes/game/GameObject.h>
#include <peppermint/classes/game/components/Camera.h>

using namespace peppermint::game::components;

EngineManager* engineManager;

int main() {
	stbi_set_flip_vertically_on_load(true);

	engineManager = new EngineManager();
	if (engineManager->status == -1) return -1;
	engineManager->worldManagers.push_back(new WorldManager());
	
	WorldManager* worldManager = engineManager->worldManagers[engineManager->activeWorldManager];

	// worldManager->saveWorldFile("peppermint/littleroot.pmintworld");
	// EngineManager::assetManager->saveAssetFile("peppermint/.pmintassets");

	EngineManager::assetManager->loadAssetFile("peppermint/.pmintassets");
	worldManager->assets = &EngineManager::assetManager->assets;
	worldManager->loadWorldFile("peppermint/littleroot.pmintworld");

	Camera* camCompTest = nullptr;

	for (unsigned int i = 0; i < worldManager->gameObjects.size(); i++) {
		for (unsigned int j = 0; j < worldManager->gameObjects[i]->components.size(); j++) {
			Camera* test = dynamic_cast<Camera*>(worldManager->gameObjects[i]->components[j]);
			if (test) camCompTest = test;
		}
	}

	EngineManager::windowManager->windows[0]->renderManager->activeCamera = camCompTest;

	engineManager->loop();

	delete engineManager;

	return 0;
}