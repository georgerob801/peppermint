#include <iostream>

#include <stb_image/stb_image.h>

#include <peppermint/managers/LogManager.h>

#include <peppermint/managers/EngineManager.h>

using namespace std;
using namespace glm;

using namespace peppermint;
using namespace peppermint::managers;

#include <peppermint/scripts/ScriptTypes.hpp>

#include <peppermint/Exceptions.hpp>

#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H

using namespace peppermint::game::components;

int main() {
	stbi_set_flip_vertically_on_load(true);

	EngineManager::initialise();
	if (EngineManager::status == -1) return -1;
	
	Asset* gameFileAsset = new Asset(Asset::PPMINT_GAME_FILE);
	gameFileAsset->path = (char*)"peppermint/game.pmint";
	EngineManager::setGameFile(gameFileAsset);

	EngineManager::loadFromGameFile();

	try {
		EngineManager::loop();
	} catch (std::exception e) {
		LogManager::critical(e.what());
		EngineManager::destroy();
		return -1;
	}

	EngineManager::destroy();

	return 0;
}