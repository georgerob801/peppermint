#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image/stb_image.h>

#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/EngineManager.h>

using namespace std;
using namespace glm;

using namespace peppermint;
using namespace peppermint::managers;

#include <peppermint/managers/WorldManager.h>
#include <peppermint/classes/game/GameObject.h>
#include <peppermint/classes/game/components/renderers/TilesetRenderer.h>

EngineManager* engineManager;

int main() {
	stbi_set_flip_vertically_on_load(true);

	engineManager = new EngineManager();
	if (engineManager->status == -1) return -1;

	engineManager->worldManagers.push_back(new WorldManager());
	
	WorldManager* worldManager = engineManager->worldManagers[engineManager->activeWorldManager];
	
	GameObject* go = new GameObject();
	TilesetRenderer* tileset = new TilesetRenderer(2, 6);
	// LogManager::warn(format("{}, {}", tileset->tileTypes[0], tileset->tileTypes[1]));
	Tileset* tilesetTex = new Tileset();
	tilesetTex->tileSize = 1.0f;
	tileset->tileset = tilesetTex;
	peppermint::game::components::TilesetRenderer::TileTextureMapping test = {
		.centre = vec2(0.5f, 0.5f)
	};
	tileset->textureMappings.push_back(test);
	tileset->generateVertices();
	go->components.push_back(tileset);
	
	worldManager->gameObjects.push_back(go);

	engineManager->loop();

	delete engineManager;

	return 0;
}