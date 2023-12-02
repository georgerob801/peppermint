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
#include <peppermint/classes/game/components/renderers/TilesetRenderer.h>
#include <peppermint/classes/game/components/Camera.h>
#include <peppermint/classes/rendering/Texture.h>
#include <peppermint/classes/rendering/TextureSet.h>

#include <peppermint/classes/game/components/NavigableMap.hpp>
#include <peppermint/classes/game/components/PlayerController.h>
#include <peppermint/classes/game/components/renderers/BasicPlayerRenderer.h>
#include <peppermint/classes/game/components/renderers/AnimatedTilesetRenderer.h>

#include <peppermint/classes/game/components/renderers/SpriteRenderer.h>

using namespace peppermint::game::components;

EngineManager* engineManager;

// TODO: OPENAL YOU IDIOT

/* TODO TIMEEEE
* TODO: openal
* TODO: sprite renderer component
* TODO: 
*/

int main() {
	stbi_set_flip_vertically_on_load(true);

	engineManager = new EngineManager();
	if (engineManager->status == -1) return -1;

	engineManager->windowManager->getWindow()->setName("Definitely Pokémon Emerald");
	
	/*
	WorldManager* worldManager = EngineManager::worldManagers[EngineManager::activeWorldManager];
	
#pragma region pokemon world
	GameObject* baseLayer = worldManager->createGameObject();
	GameObject* abovePlayerLayer = worldManager->createGameObject();
	abovePlayerLayer->transform->parent = baseLayer->transform;
	abovePlayerLayer->transform->position.z = 7.0f;
	int tilesetWidth = 30;
	int tilesetHeight = 26;

	AnimatedTilesetRenderer* baseLayerRenderer = new AnimatedTilesetRenderer(tilesetWidth, tilesetHeight);
	TilesetRenderer* abovePlayerLayerRenderer = new TilesetRenderer(tilesetWidth, tilesetHeight);

	Tileset* worldTileset = new Tileset();
	EngineManager::assetManager->registerAsset(worldTileset);

	Asset* worldImage0 = EngineManager::assetManager->newAsset(Asset::IMAGE);
	worldImage0->path = (char*)"peppermint/resource/pokemontileset/overworld-0.png";
	Asset* worldImage1 = EngineManager::assetManager->newAsset(Asset::IMAGE);
	worldImage1->path = (char*)"peppermint/resource/pokemontileset/overworld-1.png";
	Asset* worldImage3 = EngineManager::assetManager->newAsset(Asset::IMAGE);
	worldImage3->path = (char*)"peppermint/resource/pokemontileset/overworld-3.png";

	Texture* worldTexture0 = new Texture(worldImage0);
	EngineManager::assetManager->registerAsset(worldTexture0);
	TextureSet* worldTextureSet0 = new TextureSet();
	EngineManager::assetManager->registerAsset(worldTextureSet0);
	worldTextureSet0->textures.push_back(worldTexture0);
	worldTileset->textureSets.push_back(worldTextureSet0);

	Texture* worldTexture1 = new Texture(worldImage1);
	EngineManager::assetManager->registerAsset(worldTexture1);
	TextureSet* worldTextureSet1 = new TextureSet();
	EngineManager::assetManager->registerAsset(worldTextureSet1);
	worldTextureSet1->textures.push_back(worldTexture1);
	worldTileset->textureSets.push_back(worldTextureSet1);

	// duplicate frame
	worldTileset->textureSets.push_back(worldTextureSet0);

	Texture* worldTexture3 = new Texture(worldImage3);
	EngineManager::assetManager->registerAsset(worldTexture3);
	TextureSet* worldTextureSet3 = new TextureSet();
	EngineManager::assetManager->registerAsset(worldTextureSet3);
	worldTextureSet3->textures.push_back(worldTexture3);
	worldTileset->textureSets.push_back(worldTextureSet3);

	TilesetAnimation* worldBaseAnim = new TilesetAnimation();
	worldBaseAnim->texStartOffset = 0;
	worldBaseAnim->texStepOffset = 1;
	worldBaseAnim->end = 3;
	worldBaseAnim->start = 0;
	worldBaseAnim->step = 1;

	EngineManager::assetManager->registerAsset(worldBaseAnim);

	baseLayerRenderer->animations.push_back(worldBaseAnim);

	int numTilesPerRow = 1408 / 16;

	NavigableMap* navMap = new NavigableMap(tilesetWidth, tilesetHeight);
	baseLayer->components.push_back(navMap);

	for (int y = 0; y < tilesetHeight; y++) {
		for (int x = 0; x < tilesetWidth; x++) {
			baseLayerRenderer->tileTypes[y * tilesetWidth + x] = 68 * numTilesPerRow + 1;
			abovePlayerLayerRenderer->tileTypes[y * tilesetWidth + x] = 1;
		}
	}

	// add trees
	for (int i = 0; i < tilesetWidth; i += 2) {
		// row 0
		baseLayerRenderer->tileTypes[i] = 10 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[i + 1] = 10 * numTilesPerRow + 4;
		navMap->makeUnnavigable(i, 0);
		navMap->makeUnnavigable(i + 1, 0);

		// row 1
		baseLayerRenderer->tileTypes[tilesetWidth + i] = 9 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[tilesetWidth + i + 1] = 9 * numTilesPerRow + 4;
		navMap->makeUnnavigable(i, 1);
		navMap->makeUnnavigable(i + 1, 1);

		// row 2
		baseLayerRenderer->tileTypes[2 * tilesetWidth + i] = 10 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[2 * tilesetWidth + i + 1] = 10 * numTilesPerRow + 4;
		navMap->makeUnnavigable(i, 2);
		navMap->makeUnnavigable(i + 1, 2);

		// row 3
		baseLayerRenderer->tileTypes[3 * tilesetWidth + i] = 9 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[3 * tilesetWidth + i + 1] = 9 * numTilesPerRow + 4;
		navMap->makeUnnavigable(i, 3);
		navMap->makeUnnavigable(i + 1, 3);

		// row 4
		baseLayerRenderer->tileTypes[4 * tilesetWidth + i] = 10 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[4 * tilesetWidth + i + 1] = 10 * numTilesPerRow + 4;
		navMap->makeUnnavigable(i, 4);
		navMap->makeUnnavigable(i + 1, 4);

		// row 5
		abovePlayerLayerRenderer->tileTypes[5 * tilesetWidth + i] = 11 * numTilesPerRow + 7;
		abovePlayerLayerRenderer->tileTypes[5 * tilesetWidth + i + 1] = 11 * numTilesPerRow + 6;
		// navMap->makeUnnavigable(i, 5);
		// navMap->makeUnnavigable(i + 1, 5);
	}

	for (int y = 5; y < tilesetHeight - 1; y += 2) {
		// left side
		baseLayerRenderer->tileTypes[y * tilesetWidth] = 9 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[y * tilesetWidth + 1] = 9 * numTilesPerRow + 4;
		navMap->makeUnnavigable(0, y);
		navMap->makeUnnavigable(1, y);

		baseLayerRenderer->tileTypes[y * tilesetWidth + 2] = 9 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[y * tilesetWidth + 3] = 9 * numTilesPerRow + 4;
		navMap->makeUnnavigable(2, y);
		navMap->makeUnnavigable(3, y);

		baseLayerRenderer->tileTypes[y * tilesetWidth + 4] = 9 * numTilesPerRow + 5;
		navMap->makeUnnavigable(4, y);

		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth] = 10 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + 1] = 10 * numTilesPerRow + 4;
		navMap->makeUnnavigable(0, y + 1);
		navMap->makeUnnavigable(1, y + 1);

		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + 2] = 10 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + 3] = 10 * numTilesPerRow + 4;
		navMap->makeUnnavigable(2, y + 1);
		navMap->makeUnnavigable(3, y + 1);

		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + 4] = 10 * numTilesPerRow + 5;
		navMap->makeUnnavigable(4, y + 1);

		// right side
		if (y == 5 || y == 7) {
			baseLayerRenderer->tileTypes[y * tilesetWidth + tilesetWidth - 7] = 9 * numTilesPerRow + 4;
			baseLayerRenderer->tileTypes[y * tilesetWidth + tilesetWidth - 6] = 9 * numTilesPerRow + 5;
			baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + tilesetWidth - 7] = 10 * numTilesPerRow + 4;
			baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + tilesetWidth - 6] = 10 * numTilesPerRow + 5;
			abovePlayerLayerRenderer->tileTypes[(y + 2) * tilesetWidth + tilesetWidth - 7] = 11 * numTilesPerRow + 6;
			abovePlayerLayerRenderer->tileTypes[(y + 2) * tilesetWidth + tilesetWidth - 6] = 11 * numTilesPerRow + 7;
			navMap->makeUnnavigable(tilesetWidth - 7, y);
			navMap->makeUnnavigable(tilesetWidth - 6, y);
			navMap->makeUnnavigable(tilesetWidth - 7, y + 1);
			navMap->makeUnnavigable(tilesetWidth - 6, y + 1);

			if (y == 5) {
				baseLayerRenderer->tileTypes[y * tilesetWidth + tilesetWidth - 9] = 9 * numTilesPerRow + 4;
				baseLayerRenderer->tileTypes[y * tilesetWidth + tilesetWidth - 8] = 9 * numTilesPerRow + 5;
				baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + tilesetWidth - 9] = 10 * numTilesPerRow + 4;
				baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + tilesetWidth - 8] = 10 * numTilesPerRow + 5;
				navMap->makeUnnavigable(tilesetWidth - 9, y);
				navMap->makeUnnavigable(tilesetWidth - 8, y);
				navMap->makeUnnavigable(tilesetWidth - 9, y + 1);
				navMap->makeUnnavigable(tilesetWidth - 8, y + 1);
				abovePlayerLayerRenderer->tileTypes[(y + 2) * tilesetWidth + tilesetWidth - 9] = 11 * numTilesPerRow + 6;
				abovePlayerLayerRenderer->tileTypes[(y + 2) * tilesetWidth + tilesetWidth - 8] = 11 * numTilesPerRow + 7;
			}
		}

		baseLayerRenderer->tileTypes[y * tilesetWidth + tilesetWidth - 5] = 9 * numTilesPerRow + 4;
		baseLayerRenderer->tileTypes[y * tilesetWidth + tilesetWidth - 4] = 9 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[y * tilesetWidth + tilesetWidth - 3] = 9 * numTilesPerRow + 4;
		baseLayerRenderer->tileTypes[y * tilesetWidth + tilesetWidth - 2] = 9 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[y * tilesetWidth + tilesetWidth - 1] = 9 * numTilesPerRow + 4;
		navMap->makeUnnavigable(tilesetWidth - 5, y);
		navMap->makeUnnavigable(tilesetWidth - 4, y);
		navMap->makeUnnavigable(tilesetWidth - 3, y);
		navMap->makeUnnavigable(tilesetWidth - 2, y);
		navMap->makeUnnavigable(tilesetWidth - 1, y);
		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + tilesetWidth - 5] = 10 * numTilesPerRow + 4;
		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + tilesetWidth - 4] = 10 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + tilesetWidth - 3] = 10 * numTilesPerRow + 4;
		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + tilesetWidth - 2] = 10 * numTilesPerRow + 5;
		baseLayerRenderer->tileTypes[(y + 1) * tilesetWidth + tilesetWidth - 1] = 10 * numTilesPerRow + 4;
		navMap->makeUnnavigable(tilesetWidth - 5, y + 1);
		navMap->makeUnnavigable(tilesetWidth - 4, y + 1);
		navMap->makeUnnavigable(tilesetWidth - 3, y + 1);
		navMap->makeUnnavigable(tilesetWidth - 2, y + 1);
		navMap->makeUnnavigable(tilesetWidth - 1, y + 1);
	}

	for (int y = 0; y < 2; y += 2) {
		for (int x = 0; x < tilesetWidth; x += 2) {
			if (x != 16) {
				baseLayerRenderer->tileTypes[(23 + y) * tilesetWidth + x] = 8 * numTilesPerRow + 5;
				baseLayerRenderer->tileTypes[(24 + y) * tilesetWidth + x] = 10 * numTilesPerRow + 5;
				baseLayerRenderer->tileTypes[(25 + y) * tilesetWidth + x] = 9 * numTilesPerRow + 5;
				navMap->makeUnnavigable(x, 23 + y);
				navMap->makeUnnavigable(x, 24 + y);
				navMap->makeUnnavigable(x, 25 + y);
			}
			if (x != 14) {
				baseLayerRenderer->tileTypes[(23 + y) * tilesetWidth + x + 1] = 8 * numTilesPerRow + 4;
				baseLayerRenderer->tileTypes[(24 + y) * tilesetWidth + x + 1] = 10 * numTilesPerRow + 4;
				baseLayerRenderer->tileTypes[(25 + y) * tilesetWidth + x + 1] = 9 * numTilesPerRow + 4;
				navMap->makeUnnavigable(x + 1, 23 + y);
				navMap->makeUnnavigable(x + 1, 24 + y);
				navMap->makeUnnavigable(x + 1, 25 + y);
			}
		}
	}

	baseLayerRenderer->tileTypes[5 * tilesetWidth + 5] = 9 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[5 * tilesetWidth + 6] = 9 * numTilesPerRow + 5;
	baseLayerRenderer->tileTypes[6 * tilesetWidth + 5] = 10 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[6 * tilesetWidth + 6] = 10 * numTilesPerRow + 5;
	navMap->makeUnnavigable(5, 5);
	navMap->makeUnnavigable(5, 6);
	navMap->makeUnnavigable(6, 5);
	navMap->makeUnnavigable(6, 6);
	abovePlayerLayerRenderer->tileTypes[7 * tilesetWidth + 5] = 11 * numTilesPerRow + 6;
	abovePlayerLayerRenderer->tileTypes[7 * tilesetWidth + 6] = 11 * numTilesPerRow + 7;

	baseLayerRenderer->tileTypes[21 * tilesetWidth + 5] = 8 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[21 * tilesetWidth + 6] = 8 * numTilesPerRow + 5;
	baseLayerRenderer->tileTypes[22 * tilesetWidth + 5] = 10 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[22 * tilesetWidth + 6] = 10 * numTilesPerRow + 5;
	baseLayerRenderer->tileTypes[23 * tilesetWidth + 5] = 9 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[23 * tilesetWidth + 6] = 9 * numTilesPerRow + 5;
	navMap->makeUnnavigable(5, 21);
	navMap->makeUnnavigable(6, 21);
	navMap->makeUnnavigable(5, 22);
	navMap->makeUnnavigable(6, 22);
	navMap->makeUnnavigable(5, 23);
	navMap->makeUnnavigable(6, 23);

	baseLayerRenderer->tileTypes[21 * tilesetWidth + tilesetWidth - 7] = 8 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[21 * tilesetWidth + tilesetWidth - 6] = 8 * numTilesPerRow + 5;
	baseLayerRenderer->tileTypes[22 * tilesetWidth + tilesetWidth - 7] = 10 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[22 * tilesetWidth + tilesetWidth - 6] = 10 * numTilesPerRow + 5;
	baseLayerRenderer->tileTypes[23 * tilesetWidth + tilesetWidth - 7] = 9 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[23 * tilesetWidth + tilesetWidth - 6] = 9 * numTilesPerRow + 5;
	navMap->makeUnnavigable(tilesetWidth - 7, 21);
	navMap->makeUnnavigable(tilesetWidth - 6, 21);
	navMap->makeUnnavigable(tilesetWidth - 7, 22);
	navMap->makeUnnavigable(tilesetWidth - 6, 22);
	navMap->makeUnnavigable(tilesetWidth - 7, 23);
	navMap->makeUnnavigable(tilesetWidth - 6, 23);


	// flowers
	baseLayerRenderer->tileTypes[6 * tilesetWidth + 8] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[6 * tilesetWidth + 9] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[6 * tilesetWidth + 10] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[7 * tilesetWidth + 8] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[7 * tilesetWidth + 9] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[7 * tilesetWidth + 10] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[14 * tilesetWidth + 5] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[14 * tilesetWidth + 8] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[14 * tilesetWidth + 21] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[14 * tilesetWidth + 23] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[15 * tilesetWidth + 6] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[15 * tilesetWidth + 24] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 5] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 23] = 68 * numTilesPerRow + 4;
	baseLayerRenderer->tileTypes[17 * tilesetWidth + 24] = 68 * numTilesPerRow + 4;

	// signs
	baseLayerRenderer->tileTypes[7 * tilesetWidth + 11] = 68 * numTilesPerRow + 3;
	baseLayerRenderer->tileTypes[11 * tilesetWidth + 20] = 68 * numTilesPerRow + 3;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 12] = 68 * numTilesPerRow + 3;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 17] = 68 * numTilesPerRow + 3;
	navMap->makeUnnavigable(20, 11);
	navMap->makeUnnavigable(12, 16);
	navMap->makeUnnavigable(17, 16);

	// house bits
	baseLayerRenderer->tileTypes[7 * tilesetWidth + 12] = 68 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[15 * tilesetWidth + 10] = 68 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[15 * tilesetWidth + 19] = 68 * numTilesPerRow + 17;

	// top left house
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 7] = 63 * numTilesPerRow + 18;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 8] = 61 * numTilesPerRow + 18;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 9] = 61 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 10] = 59 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 11] = 63 * numTilesPerRow + 17;

	baseLayerRenderer->tileTypes[17 * tilesetWidth + 7] = 64 * numTilesPerRow + 18;
	baseLayerRenderer->tileTypes[17 * tilesetWidth + 8] = 62 * numTilesPerRow + 18;
	baseLayerRenderer->tileTypes[17 * tilesetWidth + 9] = 62 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[17 * tilesetWidth + 10] = 60 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[17 * tilesetWidth + 11] = 64 * numTilesPerRow + 17;

	baseLayerRenderer->tileTypes[18 * tilesetWidth + 7] = 65 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[18 * tilesetWidth + 8] = 65 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[18 * tilesetWidth + 9] = 65 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[18 * tilesetWidth + 10] = 65 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[18 * tilesetWidth + 11] = 65 * numTilesPerRow + 18;

	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 7] = 66 * numTilesPerRow + 16;
	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 8] = 66 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 9] = 66 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 10] = 66 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 11] = 66 * numTilesPerRow + 18;

	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 7] = 67 * numTilesPerRow + 16;
	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 8] = 67 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 9] = 67 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 10] = 67 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 11] = 67 * numTilesPerRow + 18;

	for (int x = 7; x <= 11; x++) {
		for (int y = 16; y <= 18; y++) {
			navMap->makeUnnavigable(x, y);
			if (x == 10 && y == 16) navMap->makeNavigable(x, y);
		}
	}

	// top right house
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 7 + 11] = 63 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 8 + 11] = 59 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 9 + 11] = 61 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 10 + 11] = 61 * numTilesPerRow + 18;
	baseLayerRenderer->tileTypes[16 * tilesetWidth + 11 + 11] = 63 * numTilesPerRow + 19;

	baseLayerRenderer->tileTypes[17 * tilesetWidth + 7 + 11] = 64 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[17 * tilesetWidth + 8 + 11] = 60 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[17 * tilesetWidth + 9 + 11] = 62 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[17 * tilesetWidth + 10 + 11] = 62 * numTilesPerRow + 18;
	baseLayerRenderer->tileTypes[17 * tilesetWidth + 11 + 11] = 64 * numTilesPerRow + 19;

	baseLayerRenderer->tileTypes[18 * tilesetWidth + 7 + 11] = 65 * numTilesPerRow + 16;
	baseLayerRenderer->tileTypes[18 * tilesetWidth + 8 + 11] = 65 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[18 * tilesetWidth + 9 + 11] = 65 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[18 * tilesetWidth + 10 + 11] = 65 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[18 * tilesetWidth + 11 + 11] = 65 * numTilesPerRow + 18;

	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 7 + 11] = 66 * numTilesPerRow + 16;
	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 8 + 11] = 66 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 9 + 11] = 66 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 10 + 11] = 66 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[19 * tilesetWidth + 11 + 11] = 66 * numTilesPerRow + 18;

	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 7 + 11] = 67 * numTilesPerRow + 16;
	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 8 + 11] = 67 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 9 + 11] = 67 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 10 + 11] = 67 * numTilesPerRow + 17;
	abovePlayerLayerRenderer->tileTypes[20 * tilesetWidth + 11 + 11] = 67 * numTilesPerRow + 18;

	for (int x = 18; x <= 22; x++) {
		for (int y = 16; y <= 18; y++) {
			navMap->makeUnnavigable(x, y);
			if (x == 19 && y == 16) navMap->makeNavigable(x, y);
		}
	}


	// actual house
	baseLayerRenderer->tileTypes[8 * tilesetWidth + 8] = 64 * numTilesPerRow + 22;
	baseLayerRenderer->tileTypes[8 * tilesetWidth + 9] = 66 * numTilesPerRow + 23;
	baseLayerRenderer->tileTypes[8 * tilesetWidth + 10] = 66 * numTilesPerRow + 23;
	baseLayerRenderer->tileTypes[8 * tilesetWidth + 11] = 62 * numTilesPerRow + 20;
	baseLayerRenderer->tileTypes[8 * tilesetWidth + 12] = 59 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[8 * tilesetWidth + 13] = 62 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[8 * tilesetWidth + 14] = 64 * numTilesPerRow + 23;

	baseLayerRenderer->tileTypes[9 * tilesetWidth + 8] = 65 * numTilesPerRow + 22;
	baseLayerRenderer->tileTypes[9 * tilesetWidth + 9] = 67 * numTilesPerRow + 23;
	baseLayerRenderer->tileTypes[9 * tilesetWidth + 10] = 67 * numTilesPerRow + 23;
	baseLayerRenderer->tileTypes[9 * tilesetWidth + 11] = 63 * numTilesPerRow + 20;
	baseLayerRenderer->tileTypes[9 * tilesetWidth + 12] = 60 * numTilesPerRow + 17;
	baseLayerRenderer->tileTypes[9 * tilesetWidth + 13] = 63 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[9 * tilesetWidth + 14] = 65 * numTilesPerRow + 23;

	baseLayerRenderer->tileTypes[10 * tilesetWidth + 8] = 66 * numTilesPerRow + 20;
	baseLayerRenderer->tileTypes[10 * tilesetWidth + 9] = 66 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[10 * tilesetWidth + 10] = 66 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[10 * tilesetWidth + 11] = 66 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[10 * tilesetWidth + 12] = 66 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[10 * tilesetWidth + 13] = 66 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[10 * tilesetWidth + 14] = 66 * numTilesPerRow + 22;

	baseLayerRenderer->tileTypes[11 * tilesetWidth + 8] = 66 * numTilesPerRow + 20;
	baseLayerRenderer->tileTypes[11 * tilesetWidth + 9] = 59 * numTilesPerRow + 18;
	baseLayerRenderer->tileTypes[11 * tilesetWidth + 10] = 59 * numTilesPerRow + 19;
	baseLayerRenderer->tileTypes[11 * tilesetWidth + 11] = 66 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[11 * tilesetWidth + 12] = 66 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[11 * tilesetWidth + 13] = 66 * numTilesPerRow + 21;
	baseLayerRenderer->tileTypes[11 * tilesetWidth + 14] = 66 * numTilesPerRow + 22;

	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 8] = 67 * numTilesPerRow + 20;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 9] = 60 * numTilesPerRow + 18;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 10] = 60 * numTilesPerRow + 19;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 11] = 67 * numTilesPerRow + 21;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 12] = 67 * numTilesPerRow + 21;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 13] = 67 * numTilesPerRow + 21;
	abovePlayerLayerRenderer->tileTypes[12 * tilesetWidth + 14] = 67 * numTilesPerRow + 22;

	for (int x = 8; x <= 14; x++) {
		for (int y = 8; y <= 11; y++) {
			navMap->makeUnnavigable(x, y);
			if (x == 12 && y == 8) navMap->makeNavigable(x, y);
		}
	}




	worldTileset->tileSize = vec2(16, 16);
	baseLayerRenderer->tileset = worldTileset;
	abovePlayerLayerRenderer->tileset = worldTileset;

	baseLayer->components.push_back(baseLayerRenderer);
	baseLayer->transform->position.z = -10.0f;

	abovePlayerLayer->components.push_back(abovePlayerLayerRenderer);

	baseLayerRenderer->generateTextures();

	worldTileset->generateDefaultTextureMappings();

	baseLayerRenderer->generateVertices();
	abovePlayerLayerRenderer->generateVertices();

#pragma endregion


	GameObject* camera = worldManager->createGameObject();

	Camera* cameraComponent = new Camera();
	camera->components.push_back(cameraComponent);
	cameraComponent->setGameObject(camera);
	cameraComponent->updateCameraVectors();

	EngineManager::windowManager->windows[0]->renderManager->activeCamera = cameraComponent;

	camera->transform->position = vec3(0.5f, 0.7f, 10.0f);
	camera->transform->rotation = vec3(0.0f, -half_pi<float>(), 0.0f);

	cameraComponent->viewScale = 1.0f;

	Tileset* playerTileset = new Tileset();
	EngineManager::assetManager->registerAsset(playerTileset);

	Asset* playerImage = EngineManager::assetManager->newAsset(Asset::ASSET_TYPE::IMAGE);
	playerImage->path = (char*)"peppermint/resource/pokemontileset/character.png";

	Texture* playerTexture = new Texture(playerImage);
	EngineManager::assetManager->registerAsset(playerTexture);
	TextureSet* playerTextureSet = new TextureSet();
	EngineManager::assetManager->registerAsset(playerTextureSet);
	playerTextureSet->textures.push_back(playerTexture);
	playerTileset->textureSets.push_back(playerTextureSet);

	BasicPlayerRenderer* playerRenderer = new BasicPlayerRenderer(1, 2);
	TilesetAnimation* testUp = new TilesetAnimation();
	TilesetAnimation* testDown = new TilesetAnimation();
	TilesetAnimation* testLeft = new TilesetAnimation();
	TilesetAnimation* testRight = new TilesetAnimation();

	EngineManager::assetManager->registerAsset(testUp);
	EngineManager::assetManager->registerAsset(testDown);
	EngineManager::assetManager->registerAsset(testLeft);
	EngineManager::assetManager->registerAsset(testRight);

	double walkAnimationTime = 0.1;

	testRight->uvStartOffset = vec2(48, 0);
	testRight->end = 3;
	testRight->uvStepOffset = vec2(0, -32);
	testRight->stepTime = walkAnimationTime;

	testUp->uvStartOffset = vec2(16, 0);
	testUp->end = 3;
	testUp->uvStepOffset = vec2(0, -32);
	testUp->stepTime = walkAnimationTime;

	testLeft->uvStartOffset = vec2(32, 0);
	testLeft->end = 3;
	testLeft->uvStepOffset = vec2(0, -32);
	testLeft->stepTime = walkAnimationTime;

	testDown->end = 3;
	testDown->uvStepOffset = vec2(0, -32);
	testDown->uvStartOffset = vec2(0, 0);
	testDown->stepTime = walkAnimationTime;

	playerRenderer->up = testUp;
	playerRenderer->down = testDown;
	playerRenderer->left = testLeft;
	playerRenderer->right = testRight;
	playerRenderer->tileTypes[0] = 4;
	playerRenderer->tileTypes[1] = 0;

	playerTileset->tileSize = vec2(16, 16);
	playerRenderer->tileset = playerTileset;

	for (int y = 224; y > 0; y -= 16) {
		for (int x = 0; x < 64; x += 16) {
			playerTileset->textureMappings.push_back(Tileset::TileTextureMapping() = {
				.centre = vec2(x + 8, y - 8)
			});
		}
	}

	playerRenderer->generateTextures();
	playerRenderer->generateVertices();

	navMap->makeUnnavigable(11, 7);

	GameObject* playerRenderOffset = worldManager->createGameObject();

	playerRenderOffset->components.push_back(playerRenderer);
	playerRenderOffset->transform->position.z = 5.0f;

	GameObject* player = worldManager->createGameObject();
	PlayerController* controller = new PlayerController();
	controller->setGameObject(player);
	controller->navMap = navMap;
	controller->speed = 5.0f;

	camera->transform->parent = player->transform;

	playerRenderOffset->transform->parent = player->transform;

	playerRenderer->pc = controller;

	player->components.push_back(controller);

	player->transform->parent = baseLayer->transform;
	player->transform->position.x = 7.0f;
	player->transform->position.y = 5.0f;

	GameObject* overWarp = worldManager->createGameObject();
	WarpTile* wp3 = new WarpTile();
	overWarp->addComponent(wp3);

	overWarp->transform->position.x = 12;
	overWarp->transform->position.y = 8;
	wp3->destinationWorld = 1;
	wp3->destinationCharacterPosition.x = 8;
	wp3->destinationCharacterPosition.y = 0;
	wp3->requiresFacing = true;
	wp3->facingToGo = WarpTile::UP;

	navMap->warpTiles.push_back(wp3);

	// worldManager->saveWorldFile("peppermint/littleroot.pmintworld");
	// EngineManager::assetManager->saveAssetFile("peppermint/.pmintassets");

	// EngineManager::assetManager->loadAssetFile("peppermint/.pmintassets");
	// worldManager->assets = &EngineManager::assetManager->assets;
	// worldManager->loadWorldFile("peppermint/littleroot.pmintworld");

	// EngineManager::windowManager->windows[0]->renderManager->activeCamera = worldManager->getFirstCamera();

#pragma region house inside

	// --------------------------- TODO ----------------------------
	// create one of the insides of a house in order to test warping
	// -------------------------------------------------------------

	EngineManager::activeWorldManager = 1;
	WorldManager* houseMan = engineManager->createWorldManager();

	GameObject* houseBaseLayer = houseMan->createGameObject();
	TilesetRenderer* houseBaseLayerRenderer = new TilesetRenderer(11, 9);
	houseBaseLayerRenderer->tileset = worldTileset;
	GameObject* houseUpperLayer = houseMan->createGameObject();
	TilesetRenderer* houseUpperLayerRenderer = new TilesetRenderer(11, 9);
	GameObject* houseMidLayer = houseMan->createGameObject();
	TilesetRenderer* houseMidLayerRenderer = new TilesetRenderer(11, 9);
	houseUpperLayerRenderer->tileset = worldTileset;
	houseMidLayerRenderer->tileset = worldTileset;
	houseUpperLayer->transform->parent = houseBaseLayer->transform->parent;
	houseMidLayer->transform->parent = houseBaseLayer->transform->parent;
	houseUpperLayer->components.push_back(houseUpperLayerRenderer);
	houseMidLayer->components.push_back(houseMidLayerRenderer);
	houseUpperLayer->transform->position.z = 5.0f;
	houseMidLayer->transform->position.z = 0.5f;
	houseUpperLayerRenderer->fill(1);
	houseMidLayerRenderer->fill(1);


	NavigableMap* hNavMap = new NavigableMap(11, 9);
	houseBaseLayer->components.push_back(hNavMap);


	for (unsigned int i = 0; i < 11; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			houseBaseLayerRenderer->setTileAt(i, j, 35);
		}
	}

	for (unsigned int i = 0; i < 9; i++) {
		houseBaseLayerRenderer->setTileAt(0, i, 33);
	}

	houseBaseLayerRenderer->setTileAt(1, 0, 42);
	houseBaseLayerRenderer->setTileAt(2, 0, 43);
	houseBaseLayerRenderer->setTileAt(3, 0, 43);
	houseBaseLayerRenderer->setTileAt(4, 0, 43);
	houseBaseLayerRenderer->setTileAt(5, 0, 43);
	houseBaseLayerRenderer->setTileAt(6, 0, 44);
	houseBaseLayerRenderer->setTileAt(1, 1, 42 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(2, 1, 43 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(3, 1, 43 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(4, 1, 43 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(5, 1, 43 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(6, 1, 44 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(1, 2, 42 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(2, 2, 43 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(3, 2, 43 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(4, 2, 43 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(5, 2, 43 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(6, 2, 44 + numTilesPerRow);
	houseBaseLayerRenderer->setTileAt(1, 3, 42 + (2 * numTilesPerRow));
	houseBaseLayerRenderer->setTileAt(2, 3, 43 + (2 * numTilesPerRow));
	houseBaseLayerRenderer->setTileAt(3, 3, 43 + (2 * numTilesPerRow));
	houseBaseLayerRenderer->setTileAt(4, 3, 43 + (2 * numTilesPerRow));
	houseBaseLayerRenderer->setTileAt(5, 3, 43 + (2 * numTilesPerRow));
	houseBaseLayerRenderer->setTileAt(6, 3, 44 + (2 * numTilesPerRow));



	houseMidLayerRenderer->setTileAt(2, 3, 43 + (4 * numTilesPerRow));
	houseMidLayerRenderer->setTileAt(3, 3, 44 + (4 * numTilesPerRow));
	houseMidLayerRenderer->setTileAt(4, 3, 45 + (4 * numTilesPerRow));

	houseMidLayerRenderer->setTileAt(2, 4, 43 + (5 * numTilesPerRow));
	houseMidLayerRenderer->setTileAt(3, 4, 44 + (5 * numTilesPerRow));
	houseMidLayerRenderer->setTileAt(4, 4, 45 + (5 * numTilesPerRow));
	for (unsigned int i = 2; i < 5; i++) {
		hNavMap->makeUnnavigable(i, 4);
	}



	houseUpperLayerRenderer->setTileAt(4, 5, 45 + (6 * numTilesPerRow));

	houseBaseLayerRenderer->setTileAt(8, 0, 40 + (2 * numTilesPerRow));
	houseBaseLayerRenderer->setTileAt(9, 0, 41 + (2 * numTilesPerRow));

	for (unsigned int i = 0; i < 7; i++) {
		houseBaseLayerRenderer->setTileAt(i, 8, 34 + numTilesPerRow);
		houseBaseLayerRenderer->setTileAt(i, 7, 35 + numTilesPerRow);

		hNavMap->makeUnnavigable(i, 8);
		hNavMap->makeUnnavigable(i, 7);

		if (i == 2 || i >= 5) {
			houseBaseLayerRenderer->setTileAt(i, 8, 36 + numTilesPerRow);
			houseBaseLayerRenderer->setTileAt(i, 7, 36);
		}
	}

	houseMidLayerRenderer->setTileAt(2, 1, 33 + numTilesPerRow);
	houseMidLayerRenderer->setTileAt(2, 2, 33 + numTilesPerRow);
	houseMidLayerRenderer->setTileAt(5, 1, 32 + numTilesPerRow);
	houseMidLayerRenderer->setTileAt(5, 2, 32 + numTilesPerRow);
	
	houseMidLayerRenderer->setTileAt(3, 1, 41 + (3 * numTilesPerRow));
	houseMidLayerRenderer->setTileAt(4, 1, 42 + (3 * numTilesPerRow));
	houseMidLayerRenderer->setTileAt(3, 2, 41 + (4 * numTilesPerRow));
	houseMidLayerRenderer->setTileAt(4, 2, 42 + (4 * numTilesPerRow));

	for (unsigned int i = 2; i < 6; i++) {
		for (unsigned int j = 1; j < 3; j++) {
			hNavMap->makeUnnavigable(i, j);
		}
	}

	for (unsigned int i = 0; i < 5; i++) {
		houseMidLayerRenderer->setTileAt(0 + i, 6, 37 + i);
		houseMidLayerRenderer->setTileAt(0 + i, 7, 37 + i + numTilesPerRow);

		hNavMap->makeUnnavigable(i, 6);
	}

	for (unsigned int i = 1; i < 5; i++) {
		houseBaseLayerRenderer->setTileAt(i, 5, 34);
		houseBaseLayerRenderer->setTileAt(i, 6, 33);
	}

	houseBaseLayerRenderer->setTileAt(5, 6, 34);
	houseBaseLayerRenderer->setTileAt(6, 6, 34);

	houseBaseLayerRenderer->setTileAt(7, 5, 43 + (3 * numTilesPerRow));
	houseBaseLayerRenderer->setTileAt(8, 5, 44 + (3 * numTilesPerRow));
	houseBaseLayerRenderer->setTileAt(9, 5, 45 + (3 * numTilesPerRow));
	houseBaseLayerRenderer->setTileAt(10, 5, 34);

	for (unsigned int i = 7; i < 11; i++) {
		houseBaseLayerRenderer->setTileAt(i, 8, 45 + i - 7 + (2 * numTilesPerRow));
		houseBaseLayerRenderer->setTileAt(i, 7, 45 + i - 7 + numTilesPerRow);
		houseBaseLayerRenderer->setTileAt(i, 6, 45 + i - 7);

		hNavMap->makeUnnavigable(i, 8);
		hNavMap->makeUnnavigable(i, 7);
		hNavMap->makeUnnavigable(i, 6);
	}

	hNavMap->makeNavigable(8, 6);

	for (unsigned int i = 8; i < 11; i++) {
		houseBaseLayerRenderer->setTileAt(i, 8, 1);
	}


	



	houseBaseLayer->components.push_back(houseBaseLayerRenderer);

	houseBaseLayerRenderer->generateVertices();
	houseUpperLayerRenderer->generateVertices();
	houseMidLayerRenderer->generateVertices();



	GameObject* warpGo = houseMan->createGameObject();
	WarpTile* wp = new WarpTile();
	warpGo->addComponent(wp);

	warpGo->transform->position.x = 8;
	warpGo->transform->position.y = 0;
	wp->destinationWorld = 0;
	wp->destinationCharacterPosition.x = 12;
	wp->destinationCharacterPosition.y = 8;
	wp->requiresFacing = true;
	wp->facingToGo = WarpTile::DOWN;
	wp->facingAtDestination = WarpTile::DOWN;

	hNavMap->warpTiles.push_back(wp);


	GameObject* warpGo2 = houseMan->createGameObject();
	WarpTile* wp2 = new WarpTile();
	warpGo2->addComponent(wp2);

	warpGo2->transform->position.x = 9;
	warpGo2->transform->position.y = 0;
	wp2->destinationWorld = 0;
	wp2->destinationCharacterPosition.x = 12;
	wp2->destinationCharacterPosition.y = 8;
	wp2->requiresFacing = true;
	wp2->facingToGo = WarpTile::DOWN;
	wp2->facingAtDestination = WarpTile::DOWN;

	hNavMap->warpTiles.push_back(wp2);


	BasicPlayerRenderer* hPlayerRenderer = new BasicPlayerRenderer(1, 2);
	hPlayerRenderer->tileset = playerTileset;

	hPlayerRenderer->up = testUp;
	hPlayerRenderer->down = testDown;
	hPlayerRenderer->left = testLeft;
	hPlayerRenderer->right = testRight;
	hPlayerRenderer->tileTypes[0] = 4;
	hPlayerRenderer->tileTypes[1] = 0;

	GameObject* hPlayerRenderOffset = houseMan->createGameObject();

	hPlayerRenderer->generateVertices();

	hPlayerRenderOffset->components.push_back(hPlayerRenderer);
	hPlayerRenderOffset->transform->position.z = 5.0f;

	GameObject* housePlayer = houseMan->createGameObject();

	PlayerController* hController = new PlayerController();
	hController->setGameObject(housePlayer);
	hController->navMap = hNavMap;
	hController->speed = 5.0f;

	housePlayer->components.push_back(hController);

	hPlayerRenderer->pc = hController;

	hPlayerRenderOffset->transform->parent = housePlayer->transform;




	GameObject* houseCam = houseMan->createGameObject();
	Camera* houseCamComp = new Camera();
	houseCamComp->setGameObject(houseCam);
	houseCam->components.push_back(houseCamComp);
	houseCamComp->updateCameraVectors();

	houseCam->transform->position = vec3(0.5f, 0.7f, 10.0f);
	houseCam->transform->rotation = vec3(0.0f, -half_pi<float>(), 0.0f);

	houseCam->transform->parent = housePlayer->transform;

	EngineManager::windowManager->windows[0]->renderManager->activeCamera = houseMan->getFirstCamera();


#pragma endregion

	

	EngineManager::assetManager->saveAssetFile("peppermint/.pmintassets");
	worldManager->saveWorldFile("peppermint/littleroot.pmintworld");
	houseMan->saveWorldFile("peppermint/littleroot-house1.pmintworld");
	
	// houseMan->assets = &EngineManager::assetManager->assets;
	// worldManager->loadWorldFile("peppermint/littleroot.pmintworld");
	// houseMan->loadWorldFile("peppermint/littleroot-house1.pmintworld");
	*/

	/*
	Asset* assetFile = EngineManager::assetManager->newAsset(Asset::PPMINT_GAME_FILE);
	assetFile->path = (char*)"peppermint/.pmintassets";
	EngineManager::assetManager->loadAssetFile(assetFile);

	WorldManager* wm0 = EngineManager::createWorldManager();
	Asset* wm0FileAsset = EngineManager::assetManager->newAsset(Asset::PPMINT_WORLD_FILE);
	wm0FileAsset->path = (char*)"peppermint/littleroot.pmintworld";
	wm0->setWorldFileAsset(wm0FileAsset);

	WorldManager* wm1 = EngineManager::createWorldManager();
	Asset* wm1FileAsset = EngineManager::assetManager->newAsset(Asset::PPMINT_WORLD_FILE);
	wm1FileAsset->path = (char*)"peppermint/littleroot-house1.pmintworld";
	wm1->setWorldFileAsset(wm1FileAsset);
	
	for (unsigned int i = 0; i < EngineManager::worldManagers.size(); i++) {
		EngineManager::worldManagers[i]->assets = &EngineManager::assetManager->assets;
	}

	EngineManager::activeWorldManager = 1;
	wm1->initialiseFromWorldFile();

	EngineManager::windowManager->windows[0]->renderManager->activeCamera = wm1->getFirstCamera();
	
	Asset* gameFileAsset = EngineManager::assetManager->newAsset(Asset::PPMINT_GAME_FILE);
	gameFileAsset->path = (char*)"peppermint/pokemon.pmint";
	EngineManager::setGameFile(gameFileAsset);


	
	EngineManager::goToWorld(0);
	wm0->worldAsset->path = (char*)"peppermint/new/littleroot.world";
	wm0->saveWorldFile();
	EngineManager::goToWorld(1);
	wm1->worldAsset->path = (char*)"peppermint/new/littleroot-1.world";
	wm1->saveWorldFile();
	EngineManager::saveGameFile();
	EngineManager::assetManager->saveAssetFile();*/


	Asset* gameFileAsset = new Asset(Asset::PPMINT_GAME_FILE);
	gameFileAsset->path = (char*)"peppermint/pokemon.pmint";
	engineManager->setGameFile(gameFileAsset);

	EngineManager::loadFromGameFile();


	WorldManager* wm = EngineManager::worldManagers[0];

	GameObject* go = wm->createGameObject();

	SpriteRenderer* sr = new SpriteRenderer();
	Asset* imageAsset = EngineManager::assetManager->newAsset(Asset::IMAGE);
	imageAsset->path = (char*)"peppermint/resource/texture.png";
	
	Texture* tex = new Texture(imageAsset);

	TextureSet* texSet = new TextureSet();
	texSet->addTexture(tex);

	sr->textureSet = texSet;

	go->addComponent(sr);

	sr->size = vec2(79, 28);

	sr->generateTextures();
	sr->generateVertices();

	go->transform->position.z = 1.0f;
	go->transform->position.x = 1.0f;
	go->transform->position.y = 1.0f;

	go->transform->parent = ((GameObject*)wm->getFirstComponent<PlayerController>()->getGameObject())->transform;

	engineManager->loop();

	delete engineManager;

	return 0;
}