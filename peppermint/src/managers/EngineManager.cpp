#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <peppermint/managers/EngineManager.h>

#include <peppermint/Exceptions.hpp>

#include <format>
#include <stb_image/stb_image.h>
#include <peppermint/managers/InputManager.h>

#include <fstream>

using namespace peppermint::managers;

double EngineManager::deltaTime;
double EngineManager::lastFrame;
peppermint::Asset* EngineManager::gameFile;

AssetManager* EngineManager::assetManager = new AssetManager();
WindowManager* EngineManager::windowManager = new WindowManager();

vector<WorldManager*> EngineManager::worldManagers = vector<WorldManager*>();
unsigned int EngineManager::activeWorldManager = 0;
unsigned int EngineManager::initialWorldIndex = 0;

EngineManager::EngineManager() {
	this->status = 0;
	LogManager::info("Started peppermint");
	LogManager::debug("Initialising GLFW");
	glfwInit();
	LogManager::debug("Initialised GLFW");

	LogManager::debug(std::format("Setting OpenGL version to {}.{}", majorVersion, minorVersion));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

	// glfwWindowHint(GLFW_SAMPLES, 4);

	LogManager::debug(std::format("Set OpenGL version to {}.{}", majorVersion, minorVersion));
	LogManager::debug("Setting OpenGL to core profile.");
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	LogManager::debug("Set OpenGL to core profile.");

	if (windowManager->status == -1) {
		LogManager::critical("Failed to create window manager");
		status = -1;
		return;
	}
	LogManager::debug(std::format("Created window manager at {}", (void*)windowManager));

	Window* currentWindow = windowManager->createWindow();
	if (windowManager->status == -1) this->status = -1;

	LogManager::debug(std::format("Setting current window to window at {}", (void*)currentWindow));
	windowManager->setCurrentWindow(currentWindow);
	LogManager::debug(std::format("Set current window to window at {}", (void*)currentWindow));

	LogManager::debug("Initialising GLAD");
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LogManager::critical("Failed to initialise GLAD");
		status = -1;
		return;
	}
	LogManager::debug("Initialised GLAD successfully");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	EngineManager::activeWorldManager = 0;
}

EngineManager::~EngineManager() {
	LogManager::info("Terminating peppermint");
	LogManager::debug("Terminating GLFW");
	glfwTerminate();
	LogManager::debug("Terminated GLFW");
	LogManager::debug("Deleting AssetManager");
	delete EngineManager::assetManager;
	LogManager::debug("Deleting EngineManager");
	delete EngineManager::windowManager;
}

void EngineManager::updateDeltaTime() {
	double time = glfwGetTime();
	EngineManager::deltaTime = time - EngineManager::lastFrame;
	EngineManager::lastFrame = time;
}

double EngineManager::vSyncTime() {
	return glfwGetTime() - EngineManager::lastFrame;
}

WorldManager* EngineManager::createWorldManager() {
	WorldManager* wm = new WorldManager();
	EngineManager::worldManagers.push_back(wm);

	return wm;
}

void EngineManager::goToWorld(unsigned int worldIndex) {
	// unload current world
	EngineManager::worldManagers[EngineManager::activeWorldManager]->unload();

	// load new world
	EngineManager::activeWorldManager = worldIndex;
	EngineManager::worldManagers[EngineManager::activeWorldManager]->initialiseFromWorldFile();
	EngineManager::worldManagers[EngineManager::activeWorldManager]->stopProcessingWorld = false;

	EngineManager::windowManager->windows[0]->renderManager->activeCamera = EngineManager::worldManagers[EngineManager::activeWorldManager]->getFirstCamera();
}

void EngineManager::loop() {
	glEnable(GL_DEPTH_TEST);

	// just for test camera
	// Transform* cam = ((GameObject*)EngineManager::windowManager->windows[0]->renderManager->activeCamera->getGameObject())->transform;
	// Camera* camComp = EngineManager::windowManager->windows[0]->renderManager->activeCamera;
	// GLFWwindow* win = EngineManager::windowManager->windows[0]->getAddress();

#pragma region window icons
	stbi_set_flip_vertically_on_load(false);
	GLFWimage images[2];
	images[0].pixels = stbi_load("peppermint/resource/window-icon.png", &images[0].width, &images[0].height, 0, 4);
	images[1].pixels = stbi_load("peppermint/resource/window-icon-small.png", &images[1].width, &images[1].height, 0, 4);
	
	for (unsigned int i = 0; i < EngineManager::windowManager->windows.size(); i++) {
		glfwSetWindowIcon(EngineManager::windowManager->windows[i]->getAddress(), 2, images);
	}

	stbi_image_free(images[0].pixels);
	stbi_image_free(images[1].pixels);
	stbi_set_flip_vertically_on_load(true);
#pragma endregion

	unsigned int lastWmI = this->activeWorldManager;

	while (EngineManager::windowManager->windows.size() != 0) {
		if (this->status == -1) throw std::exception("Failed to run peppermint.");

		this->updateDeltaTime();

		for (int i = 0; i < EngineManager::windowManager->windows.size(); i++) {
			InputManager::setWindow(EngineManager::windowManager->windows[i]);

			//if (this->activeWorldManager != lastWmI) {
			//	EngineManager::windowManager->windows[i]->renderManager->activeCamera = EngineManager::worldManagers[EngineManager::activeWorldManager]->getFirstCamera();
			//}

			lastWmI = this->activeWorldManager;

			// awake
			if (!this->worldManagers[this->activeWorldManager]->initialised) {
				EngineManager::windowManager->windows[i]->renderManager->activeCamera = this->worldManagers[this->activeWorldManager]->getFirstCamera();
				this->worldManagers[this->activeWorldManager]->awake();
				this->worldManagers[this->activeWorldManager]->initialised = true;
			}

			// discard frame if world changed, restart loop process
			if (this->activeWorldManager != lastWmI) continue;

			// start
			this->worldManagers[this->activeWorldManager]->start();

			// discard frame if world changed, restart loop process
			if (this->activeWorldManager != lastWmI) continue;

			// loop
			this->worldManagers[this->activeWorldManager]->loop(EngineManager::windowManager->windows[i]);

			// discard frame if world changed, restart loop process
			if (this->activeWorldManager != lastWmI) continue;

			EngineManager::windowManager->windows[i]->renderFrame();
			EngineManager::windowManager->windows[i]->swapBuffers();

			if (EngineManager::windowManager->windows[i]->shouldClose()) {
				Window* windowToDelete = EngineManager::windowManager->windows[i];
				EngineManager::windowManager->windows.erase(EngineManager::windowManager->windows.begin() + i);
				delete windowToDelete;
			}
		}

		while (this->vSyncTime() < 1.0f / 60.0f) { }
		// LogManager::debug(std::format("{} fps", round(1.0f / this->vSyncTime())));

		glfwPollEvents();
	}
}

void EngineManager::setGameFile(Asset* gameFile) {
	EngineManager::gameFile = gameFile;
}

void EngineManager::saveGameFile() {
	if (EngineManager::gameFile == nullptr) throw peppermint::exceptions::serialisation::game::NoGameFilePathException();

	std::ofstream gameFileFS(EngineManager::gameFile->path, std::ios::binary | std::ios::trunc);

	vector<byte> out;

	out.push_back((byte)0x03);
	out.push_back((byte)0x00);

	while (out.size() < 16) out.push_back((byte)0x00);

	// asset path
	std::string assetPathStr(EngineManager::assetManager->assetFileAsset->path);
	unsigned int assetPathLen = assetPathStr.size();
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(reinterpret_cast<byte*>(&assetPathLen)[i]);
	}

	// asset path str?
	for (unsigned int i = 0; i < assetPathLen; i++) {
		out.push_back(reinterpret_cast<byte*>(&assetPathStr[i])[0]);
	}

	// number of world files
	unsigned int numWorldFiles = EngineManager::worldManagers.size();
	byte* numWorldFilesB = reinterpret_cast<byte*>(&numWorldFiles);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(numWorldFilesB[i]);
	}

	// initial world index
	byte* initialWorldIndexB = reinterpret_cast<byte*>(&EngineManager::initialWorldIndex);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(initialWorldIndexB[i]);
	}

	// the actual world file asset ids
	for (unsigned int i = 0; i < EngineManager::worldManagers.size(); i++) {
		byte* wmAIDB = reinterpret_cast<byte*>(&EngineManager::worldManagers[i]->worldAsset);
		for (unsigned int j = 0; j < sizeof(void*); j++) {
			out.push_back(wmAIDB[j]);
		}
	}

	if (out.size() > 0) gameFileFS.write(reinterpret_cast<const char*>(&out[0]), out.size());
}

void EngineManager::loadFromGameFile() {
	std::ifstream gameFile(EngineManager::gameFile->path, std::ios::binary | std::ios::in);
	gameFile.unsetf(std::ios::skipws);

	std::streampos fileSize;

	gameFile.seekg(0, std::ios::end);
	fileSize = gameFile.tellg();
	gameFile.seekg(0, std::ios::beg);

	std::vector<unsigned char> chars;
	chars.reserve(fileSize);

	chars.insert(chars.begin(), std::istream_iterator<unsigned char>(gameFile), std::istream_iterator<unsigned char>());
	
	std::vector<byte> bytes;
	bytes.reserve(fileSize);
	for (unsigned int i = 0; i < chars.size(); i++) {
		bytes.push_back((byte)chars[i]);
	}

	if (bytes.size() < 16) {
		throw peppermint::exceptions::serialisation::game::CorruptedFileException();
	}

	if (bytes[0x00] != (byte)0x03) {
		throw peppermint::exceptions::serialisation::game::InvalidFileTypeException();
	}

	EngineManager::worldManagers.clear();
	vector<WorldManager*>().swap(EngineManager::worldManagers);

	delete EngineManager::assetManager;

	unsigned long long position = 0x10;

	unsigned int assetFilePathLength = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	std::string assetFilePath = "";
	for (unsigned int i = 0; i < assetFilePathLength; i++) {
		assetFilePath += *reinterpret_cast<char*>(&bytes[position]);
		position += sizeof(char);
	}

	// LOAD THE ASSET MANAGER HERE
	Asset* assetManagerAsset = new Asset(Asset::PPMINT_ASSET_FILE);
	// memory managed by asset deconstructor
	char* assetManagerPathCStr = new char();
	assetManagerPathCStr = (char*)assetFilePath.c_str();
	assetManagerAsset->path = assetManagerPathCStr;

	AssetManager* am = new AssetManager();
	EngineManager::assetManager = am;
	am->loadAssetFile(assetManagerAsset);

	// eeee

	unsigned int numWorldAssets = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	EngineManager::initialWorldIndex = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	vector<void*> worldAssetIDs;
	worldAssetIDs.reserve(numWorldAssets);

	for (unsigned int i = 0; i < numWorldAssets; i++) {
		worldAssetIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
		position += sizeof(void*);
	}

	// LOAD ACTUAL WORLDS HERE
	for (unsigned int i = 0; i < worldAssetIDs.size(); i++) {
		// find asset
		void* worldAssetID = worldAssetIDs[i];
		vector<Asset*>::iterator index = find_if(EngineManager::assetManager->assets.begin(), EngineManager::assetManager->assets.end(), [worldAssetID](Asset* item) { return item->serialisedID == worldAssetID; });

		if (index == EngineManager::assetManager->assets.end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

		WorldManager* wm = EngineManager::createWorldManager();
		wm->assets = &EngineManager::assetManager->assets;
		wm->setWorldFileAsset(*index);
	}

	LogManager::info("Loaded game");

	LogManager::debug(format("Going to initial world (index {})", EngineManager::initialWorldIndex));
	EngineManager::goToWorld(EngineManager::initialWorldIndex);
}