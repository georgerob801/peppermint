#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <peppermint/managers/EngineManager.h>

#include <format>
#include <stb_image/stb_image.h>
#include <peppermint/managers/InputManager.h>

using namespace peppermint::managers;

double EngineManager::deltaTime;
double EngineManager::lastFrame;

AssetManager* EngineManager::assetManager = new AssetManager();
WindowManager* EngineManager::windowManager = new WindowManager();

vector<WorldManager*> EngineManager::worldManagers = vector<WorldManager*>();
unsigned int EngineManager::activeWorldManager = 0;

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