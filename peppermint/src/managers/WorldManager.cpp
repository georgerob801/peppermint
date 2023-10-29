#include <peppermint/managers/WorldManager.h>
#include <type_traits>

#include <peppermint/classes/game/components/renderers/Renderer.h>
#include <peppermint/classes/rendering/RenderStack.h>

#include <peppermint/classes/rendering/TilesetAnimationStateInfomation.hpp>

#include <algorithm>

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