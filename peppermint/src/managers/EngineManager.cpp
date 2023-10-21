#include <peppermint/managers/EngineManager.h>
#include <format>

using namespace peppermint::managers;

double EngineManager::deltaTime;
double EngineManager::lastFrame;

EngineManager::EngineManager() {
	this->status = 0;
	LogManager::info("Started peppermint");
	LogManager::debug("Initialising GLFW");
	glfwInit();
	LogManager::debug("Initialised GLFW");

	LogManager::debug(std::format("Setting OpenGL version to {}.{}", majorVersion, minorVersion));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	LogManager::debug(std::format("Set OpenGL version to {}.{}", majorVersion, minorVersion));
	LogManager::debug("Setting OpenGL to core profile.");
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	LogManager::debug("Set OpenGL to core profile.");
	
	LogManager::debug("Creating window manager");
	this->windowManager = new WindowManager();


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
}

EngineManager::~EngineManager() {
	LogManager::info("Terminating peppermint");
	LogManager::debug("Terminating GLFW");
	glfwTerminate();
	LogManager::debug("Terminated GLFW");
	LogManager::debug("Deleting EngineManager");
	delete this->windowManager;
}

void EngineManager::updateDeltaTime() {
	double time = glfwGetTime();
	EngineManager::deltaTime = time - EngineManager::lastFrame;
	EngineManager::lastFrame = time;
}

double EngineManager::vSyncTime() {
	return glfwGetTime() - EngineManager::lastFrame;
}

void EngineManager::loop() {
	while (this->windowManager->windows.size() != 0) {
		if (this->status == -1) throw std::exception("Failed to start peppermint.");

		this->updateDeltaTime();

		for (int i = 0; i < this->windowManager->windows.size(); i++) {
			this->worldManagers[this->activeWorldManager]->loop(this->windowManager->windows[i]);

			this->windowManager->windows[i]->renderFrame();
			this->windowManager->windows[i]->swapBuffers();

			if (this->windowManager->windows[i]->shouldClose()) {
				Window* windowToDelete = this->windowManager->windows[i];
				this->windowManager->windows.erase(this->windowManager->windows.begin() + i);
				delete windowToDelete;
			}
		}

		while (this->vSyncTime() < 1.0f / 60.0f) { }
		// LogManager::debug(std::format("{} fps", round(1.0f / this->vSyncTime())));

		glfwPollEvents();
	}
}