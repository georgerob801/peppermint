#include <peppermint/managers/WorldManager.h>
#include <type_traits>

#include <peppermint/classes/game/components/renderers/Renderer.h>
#include <peppermint/classes/rendering/RenderStack.h>

using namespace peppermint::managers;

// this will be exponentially more laggy and will require refactoring
void WorldManager::start(Window* window) {
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
				peppermint::rendering::RenderItem renderItem = {
					.shader = shader,
					.mesh = rendererComponent->getOrGenerateMesh()
				};

				window->renderManager->activeRenderStack->renderItems.push_back(renderItem);
			}
		}
	}
}