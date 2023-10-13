#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "peppermint/include/stb_image/stb_image.h"

#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/EngineManager.h>

using namespace std;
using namespace glm;

using namespace peppermint;
using namespace peppermint::managers;

int width = 500;
int height = 500;

EngineManager* engineManager;

int main() {
	engineManager = new EngineManager();
	if (engineManager->status == -1) return -1;

	Window* window = engineManager->windowManager->getWindow();
	if (engineManager->status == -1) return -1;

	window->makeCurrentContext();
	if (engineManager->status == -1) return -1;

	glViewport(0, 0, width, height);

	// glfwSetCursorPosCallback(window, );

	glEnable(GL_CULL_FACE);

	while (!window->shouldClose()) {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window->swapBuffers();
		glfwPollEvents();
	}

	delete engineManager;

	return 0;
}