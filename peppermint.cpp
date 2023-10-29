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
#include <peppermint/classes/game/components/Camera.h>
#include <peppermint/classes/rendering/Texture.h>
#include <peppermint/classes/rendering/TextureSet.h>

#include <peppermint/classes/game/components/NavigableMap.hpp>
#include <peppermint/classes/game/components/PlayerController.h>
#include <peppermint/classes/game/components/renderers/BasicPlayerRenderer.h>

using namespace peppermint::game::components;

EngineManager* engineManager;

int main() {
	stbi_set_flip_vertically_on_load(true);

	engineManager = new EngineManager();
	if (engineManager->status == -1) return -1;

	engineManager->worldManagers.push_back(new WorldManager());
	
	WorldManager* worldManager = engineManager->worldManagers[engineManager->activeWorldManager];
	
	GameObject* go = worldManager->createGameObject();
	const int tilesetWidth = 30;
	const int tilesetHeight = 30;
	TilesetRenderer* baseLayer = new TilesetRenderer(tilesetWidth, tilesetHeight);

#pragma region tile 1 setup
	// tileset setup
	baseLayer->tileTypes[4] = 282;
	baseLayer->tileTypes[5] = 283;
	baseLayer->tileTypes[6] = 362;
	baseLayer->tileTypes[7] = 363;
	baseLayer->tileTypes[8] = 283;
	baseLayer->tileTypes[9] = 284;

	baseLayer->tileTypes[tilesetWidth + 1] = 200;
	baseLayer->tileTypes[tilesetWidth + 2] = 201;
	baseLayer->tileTypes[tilesetWidth + 3] = 202;
	baseLayer->tileTypes[tilesetWidth + 4] = 282;
	baseLayer->tileTypes[tilesetWidth + 5] = 283;
	baseLayer->tileTypes[tilesetWidth + 6] = 283;
	baseLayer->tileTypes[tilesetWidth + 7] = 283;
	baseLayer->tileTypes[tilesetWidth + 8] = 283;
	baseLayer->tileTypes[tilesetWidth + 9] = 284;

	baseLayer->tileTypes[2 * tilesetWidth + 1] = 160;
	baseLayer->tileTypes[2 * tilesetWidth + 2] = 161;
	baseLayer->tileTypes[2 * tilesetWidth + 3] = 162;
	baseLayer->tileTypes[2 * tilesetWidth + 4] = 242;
	baseLayer->tileTypes[2 * tilesetWidth + 5] = 243;
	baseLayer->tileTypes[2 * tilesetWidth + 6] = 243;
	baseLayer->tileTypes[2 * tilesetWidth + 7] = 243;
	baseLayer->tileTypes[2 * tilesetWidth + 8] = 243;
	baseLayer->tileTypes[2 * tilesetWidth + 9] = 244;

	baseLayer->tileTypes[3 * tilesetWidth + 1] = 160;
	baseLayer->tileTypes[3 * tilesetWidth + 2] = 161;
	baseLayer->tileTypes[3 * tilesetWidth + 3] = 162;
	baseLayer->tileTypes[3 * tilesetWidth + 5] = 1240;
	baseLayer->tileTypes[3 * tilesetWidth + 6] = 1241;
	baseLayer->tileTypes[3 * tilesetWidth + 7] = 1241;
	baseLayer->tileTypes[3 * tilesetWidth + 8] = 1242;

	baseLayer->tileTypes[4 * tilesetWidth + 1] = 160;
	baseLayer->tileTypes[4 * tilesetWidth + 2] = 161;
	baseLayer->tileTypes[4 * tilesetWidth + 3] = 162;
	baseLayer->tileTypes[4 * tilesetWidth + 5] = 1200;
	baseLayer->tileTypes[4 * tilesetWidth + 6] = 1400;
	baseLayer->tileTypes[4 * tilesetWidth + 7] = 1401;
	baseLayer->tileTypes[4 * tilesetWidth + 8] = 1280;

	baseLayer->tileTypes[5 * tilesetWidth + 1] = 160;
	baseLayer->tileTypes[5 * tilesetWidth + 2] = 161;
	baseLayer->tileTypes[5 * tilesetWidth + 3] = 162;
	baseLayer->tileTypes[5 * tilesetWidth + 5] = 1200;
	baseLayer->tileTypes[5 * tilesetWidth + 6] = 1401;
	baseLayer->tileTypes[5 * tilesetWidth + 7] = 1360;
	baseLayer->tileTypes[5 * tilesetWidth + 8] = 1401;
	baseLayer->tileTypes[5 * tilesetWidth + 9] = 1202;

	baseLayer->tileTypes[6 * tilesetWidth + 1] = 160;
	baseLayer->tileTypes[6 * tilesetWidth + 2] = 161;
	baseLayer->tileTypes[6 * tilesetWidth + 3] = 162;
	baseLayer->tileTypes[6 * tilesetWidth + 5] = 1160;
	baseLayer->tileTypes[6 * tilesetWidth + 6] = 1161;
	baseLayer->tileTypes[6 * tilesetWidth + 7] = 1161;
	baseLayer->tileTypes[6 * tilesetWidth + 8] = 1161;
	baseLayer->tileTypes[6 * tilesetWidth + 9] = 1162;

	baseLayer->tileTypes[7 * tilesetWidth + 1] = 120;
	baseLayer->tileTypes[7 * tilesetWidth + 2] = 121;
	baseLayer->tileTypes[7 * tilesetWidth + 3] = 122;
	baseLayer->tileTypes[7 * tilesetWidth + 4] = 1254;
	baseLayer->tileTypes[7 * tilesetWidth + 5] = 1255;
	baseLayer->tileTypes[7 * tilesetWidth + 6] = 1255;
	baseLayer->tileTypes[7 * tilesetWidth + 7] = 1255;
	baseLayer->tileTypes[7 * tilesetWidth + 8] = 1255;
	baseLayer->tileTypes[7 * tilesetWidth + 9] = 1255;
	baseLayer->tileTypes[7 * tilesetWidth + 10] = 1256;

	baseLayer->tileTypes[8 * tilesetWidth + 4] = 1214;
	baseLayer->tileTypes[8 * tilesetWidth + 5] = 1215;
	baseLayer->tileTypes[8 * tilesetWidth + 6] = 1215;
	baseLayer->tileTypes[8 * tilesetWidth + 7] = 1215;
	baseLayer->tileTypes[8 * tilesetWidth + 8] = 1215;
	baseLayer->tileTypes[8 * tilesetWidth + 9] = 1215;
	baseLayer->tileTypes[8 * tilesetWidth + 10] = 1216;

	baseLayer->tileTypes[9 * tilesetWidth + 4] = 1214;
	baseLayer->tileTypes[9 * tilesetWidth + 5] = 1215;
	baseLayer->tileTypes[9 * tilesetWidth + 6] = 1215;
	baseLayer->tileTypes[9 * tilesetWidth + 7] = 1215;
	baseLayer->tileTypes[9 * tilesetWidth + 8] = 1215;
	baseLayer->tileTypes[9 * tilesetWidth + 9] = 1215;
	baseLayer->tileTypes[9 * tilesetWidth + 10] = 1216;

	baseLayer->tileTypes[10 * tilesetWidth + 4] = 1174;
	baseLayer->tileTypes[10 * tilesetWidth + 5] = 1175;
	baseLayer->tileTypes[10 * tilesetWidth + 6] = 1175;
	baseLayer->tileTypes[10 * tilesetWidth + 7] = 1175;
	baseLayer->tileTypes[10 * tilesetWidth + 8] = 1175;
	baseLayer->tileTypes[10 * tilesetWidth + 9] = 1175;
	baseLayer->tileTypes[10 * tilesetWidth + 10] = 1176;

#pragma endregion

	GameObject* abovePlayerLayer = worldManager->createGameObject();
	TilesetRenderer* abovePlayerLayerRenderer = new TilesetRenderer(tilesetWidth, tilesetHeight);

	for (int i = 0; i < tilesetHeight * tilesetWidth; i++) {
		abovePlayerLayerRenderer->tileTypes[i] = 1072;
	}

	abovePlayerLayerRenderer->tileTypes[10 * tilesetWidth + 5] = 86;
	abovePlayerLayerRenderer->tileTypes[10 * tilesetWidth + 6] = 87;
	abovePlayerLayerRenderer->tileTypes[10 * tilesetWidth + 7] = 88;
	abovePlayerLayerRenderer->tileTypes[10 * tilesetWidth + 8] = 89;
	abovePlayerLayerRenderer->tileTypes[10 * tilesetWidth + 9] = 90;

	abovePlayerLayerRenderer->tileTypes[11 * tilesetWidth + 5] = 46;
	abovePlayerLayerRenderer->tileTypes[11 * tilesetWidth + 6] = 47;
	abovePlayerLayerRenderer->tileTypes[11 * tilesetWidth + 7] = 48;
	abovePlayerLayerRenderer->tileTypes[11 * tilesetWidth + 8] = 49;
	abovePlayerLayerRenderer->tileTypes[11 * tilesetWidth + 9] = 50;

	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 5] = 6;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 6] = 7;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 7] = 8;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 8] = 9;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 9] = 10;

	abovePlayerLayer->transform->position.z = 15.0f;

#pragma region tile 2 setup
	GameObject* belowPlayerLayer = engineManager->worldManagers[engineManager->activeWorldManager]->createGameObject();
	TilesetRenderer* upperLayer = new TilesetRenderer(tilesetWidth, tilesetHeight);

	for (int i = 0; i < tilesetHeight * tilesetWidth; i++) {
		upperLayer->tileTypes[i] = 1072;
	}

	upperLayer->tileTypes[8] = 5;

	upperLayer->tileTypes[tilesetWidth] = 206;
	upperLayer->tileTypes[tilesetWidth + 5] = 2;
	
	upperLayer->tileTypes[8 * tilesetWidth + 5] = 166;
	upperLayer->tileTypes[8 * tilesetWidth + 6] = 167;
	upperLayer->tileTypes[8 * tilesetWidth + 7] = 168;
	upperLayer->tileTypes[8 * tilesetWidth + 8] = 169;
	upperLayer->tileTypes[8 * tilesetWidth + 9] = 170;

	upperLayer->tileTypes[9 * tilesetWidth + 5] = 126;
	upperLayer->tileTypes[9 * tilesetWidth + 6] = 127;
	upperLayer->tileTypes[9 * tilesetWidth + 7] = 128;
	upperLayer->tileTypes[9 * tilesetWidth + 8] = 129;
	upperLayer->tileTypes[9 * tilesetWidth + 9] = 130;

	belowPlayerLayer->transform->position.z = 5.0f;

#pragma endregion

	Tileset* tilesetTex = new Tileset();

	Texture* testTex = new Texture((char*)"peppermint/resource/testtileset/overworld.png");
	TextureSet* testTextureSet = new TextureSet();
	testTextureSet->textures.push_back(testTex);

	tilesetTex->textureSets.push_back(testTextureSet);

	tilesetTex->tileSize = vec2(16, 16);
	baseLayer->tileset = tilesetTex;
	upperLayer->tileset = tilesetTex;
	abovePlayerLayerRenderer->tileset = tilesetTex;

	for (int y = 576; y > 0; y -= 16) {
		for (int x = 0; x < 640; x += 16) {
			// move this storage to the Tileset class
			baseLayer->tileset->textureMappings.push_back(Tileset::TileTextureMapping() = {
				.centre = vec2(x + 8, y - 8)
			});
		}
	}

	baseLayer->generateTextures();
	baseLayer->generateVertices();
	upperLayer->generateVertices();
	abovePlayerLayerRenderer->generateVertices();

	go->components.push_back(baseLayer);
	belowPlayerLayer->components.push_back(upperLayer);
	belowPlayerLayer->transform->parent = go->transform;
	abovePlayerLayer->components.push_back(abovePlayerLayerRenderer);
	abovePlayerLayer->transform->parent = go->transform;

	go->transform->position.z = -10.0f;




	// TilesetRenderer* playerRenderer = new TilesetRenderer(1, 2);

	BasicPlayerRenderer* playerRenderer = new BasicPlayerRenderer(1, 2);
	TilesetAnimation* testUp = new TilesetAnimation();
	TilesetAnimation* testDown = new TilesetAnimation();
	TilesetAnimation* testLeft = new TilesetAnimation();
	TilesetAnimation* testRight = new TilesetAnimation();

	double walkAnimationTime = 0.14;

	testRight->uvStartOffset = vec2(0, -32);
	testRight->end = 3;
	testRight->uvStepOffset = vec2(16, 0);
	testRight->stepTime = walkAnimationTime;

	testUp->uvStartOffset = vec2(0, -64);
	testUp->end = 3;
	testUp->uvStepOffset = vec2(16, 0);
	testUp->stepTime = walkAnimationTime;

	testLeft->uvStartOffset = vec2(0, -96);
	testLeft->end = 3;
	testLeft->uvStepOffset = vec2(16, 0);
	testLeft->stepTime = walkAnimationTime;

	testDown->end = 3;
	testDown->uvStepOffset = vec2(16, 0);
	testDown->stepTime = walkAnimationTime;

	playerRenderer->up = testUp;
	playerRenderer->down = testDown;
	playerRenderer->left = testLeft;
	playerRenderer->right = testRight;
	playerRenderer->tileTypes[0] = 17;
	playerRenderer->tileTypes[1] = 0;


	Tileset* playerTileset = new Tileset();
	Texture* playerTexture = new Texture((char*)"peppermint/resource/testtileset/character.png");
	TextureSet* playerTextureSet = new TextureSet();
	playerTextureSet->textures.push_back(playerTexture);
	playerTileset->textureSets.push_back(playerTextureSet);

	playerTileset->tileSize = vec2(16, 16);
	playerRenderer->tileset = playerTileset;

	for (int y = 256; y > 0; y -= 16) {
		for (int x = 0; x < 272; x += 16) {
			// move this storage to the Tileset class
			playerTileset->textureMappings.push_back(Tileset::TileTextureMapping() = {
				.centre = vec2(x + 8, y - 8)
			});
		}
	}

	playerRenderer->generateTextures();
	playerRenderer->generateVertices();


	NavigableMap* navMap = new NavigableMap(tilesetWidth, tilesetHeight);


	navMap->makeUnnavigable(0, 1);
	navMap->makeUnnavigable(4, 0);
	navMap->makeUnnavigable(4, 1);
	navMap->makeUnnavigable(4, 2);
	navMap->makeUnnavigable(5, 2);
	navMap->makeUnnavigable(6, 2);
	navMap->makeUnnavigable(7, 2);
	navMap->makeUnnavigable(8, 2);
	navMap->makeUnnavigable(9, 2);
	navMap->makeUnnavigable(9, 1);
	navMap->makeUnnavigable(9, 0);

	navMap->makeUnnavigable(5, 9);
	navMap->makeUnnavigable(6, 9);
	navMap->makeUnnavigable(7, 9);
	navMap->makeUnnavigable(8, 9);
	navMap->makeUnnavigable(9, 9);

	go->components.push_back(navMap);

	GameObject* camera = worldManager->createGameObject();

	Camera* cameraComponent = new Camera();
	cameraComponent->setGameObject(camera);
	cameraComponent->updateCameraVectors();
	engineManager->windowManager->windows[0]->renderManager->activeCamera = cameraComponent;

	camera->transform->position = vec3(0.5f, 0.7f, 10.0f);
	camera->transform->rotation = vec3(0.0f, -half_pi<float>(), 0.0f);

	cameraComponent->viewScale = 1.0f;

	GameObject* playerRenderOffset = worldManager->createGameObject();
	playerRenderOffset->components.push_back(playerRenderer);
	playerRenderOffset->transform->position.y = -0.25f;

	GameObject* player = worldManager->createGameObject();
	PlayerController* controller = new PlayerController();
	controller->setGameObject(player);
	controller->navMap = navMap;
	controller->speed = 5.0f;
	camera->transform->parent = player->transform;
	playerRenderOffset->transform->parent = player->transform;

	playerRenderer->pc = controller;

	player->components.push_back(controller);

	engineManager->loop();

	delete engineManager;

	return 0;
}