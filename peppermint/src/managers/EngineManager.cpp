#include <peppermint/managers/EngineManager.h>

#include <format>
#include <stb_image/stb_image.h>
#include <peppermint/managers/InputManager.h>

using namespace peppermint::managers;

double EngineManager::deltaTime;
double EngineManager::lastFrame;

AssetManager* EngineManager::assetManager = new AssetManager();
WindowManager* EngineManager::windowManager = new WindowManager();

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
	this->worldManagers.push_back(wm);

	return wm;
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

	for (unsigned int i = 0; i < this->worldManagers.size(); i++) {
		this->worldManagers[i]->awake();
	}
	stbi_set_flip_vertically_on_load(true);
#pragma endregion

	while (EngineManager::windowManager->windows.size() != 0) {
		if (this->status == -1) throw std::exception("Failed to start peppermint.");

		this->updateDeltaTime();

		for (int i = 0; i < EngineManager::windowManager->windows.size(); i++) {
			InputManager::setWindow(EngineManager::windowManager->windows[i]);

			this->worldManagers[this->activeWorldManager]->loop(EngineManager::windowManager->windows[i]);

			// this->worldManagers[0]->gameObjects[0]->transform->position.x = sin(glfwGetTime());
			// this->worldManagers[0]->gameObjects[0]->transform->position.y = cos(glfwGetTime());
			// ((GameObject*)EngineManager::windowManager->windows[0]->renderManager->activeCamera->getGameObject())->transform->position = vec3(sin(glfwGetTime()), 0.0f, -1.0f);

			// temporary movement
			/*if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
				cam->position -= camComp->right * (float)EngineManager::deltaTime * 3.0f;
			}
			if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
				cam->position += camComp->right * (float)EngineManager::deltaTime * 3.0f;
			}
			if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
				cam->position += normalize(cross(vec3(0.0f, 1.0f, 0.0f), camComp->right)) * (float)EngineManager::deltaTime * 3.0f;
			}
			if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
				cam->position -= normalize(cross(vec3(0.0f, 1.0f, 0.0f), camComp->right)) * (float)EngineManager::deltaTime * 3.0f;
			}
			if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS) {
				cam->position -= vec3(0.0f, 1.0f, 0.0f) * (float)EngineManager::deltaTime * 3.0f;
			}
			if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS) {
				cam->position += vec3(0.0f, 1.0f, 0.0f) * (float)EngineManager::deltaTime * 3.0f;
			}
			if (glfwGetKey(win, GLFW_KEY_I) == GLFW_PRESS) {
				cam->rotation.x += 1.0f * (float)EngineManager::deltaTime;
				if (cam->rotation.x >= glm::half_pi<float>()) cam->rotation.x = glm::half_pi<float>() - 0.001f;
			}
			if (glfwGetKey(win, GLFW_KEY_K) == GLFW_PRESS) {
				cam->rotation.x -= 1.0f * (float)EngineManager::deltaTime;
				if (cam->rotation.x <= -glm::half_pi<float>()) cam->rotation.x = -glm::half_pi<float>() + 0.001f;
			}
			if (glfwGetKey(win, GLFW_KEY_L) == GLFW_PRESS) {
				cam->rotation.y += 1.0f * (float)EngineManager::deltaTime;
				if (cam->rotation.y >= glm::pi<float>()) cam->rotation.y = -glm::pi<float>() + 0.001f;
			}
			if (glfwGetKey(win, GLFW_KEY_J) == GLFW_PRESS) {
				cam->rotation.y -= 1.0f * (float)EngineManager::deltaTime;
				if (cam->rotation.y <= -glm::pi<float>()) cam->rotation.y = glm::pi<float>() - 0.001f;
			}*/

			/*if (glfwGetKey(win, GLFW_KEY_G) == GLFW_PRESS) {
				camComp->viewScale += 1.0f * (float)EngineManager::deltaTime;
			}
			if (glfwGetKey(win, GLFW_KEY_H) == GLFW_PRESS) {
				camComp->viewScale -= 1.0f * (float)EngineManager::deltaTime;
			}*/

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