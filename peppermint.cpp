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

EngineManager* engineManager;

int main() {
	engineManager = new EngineManager();
	if (engineManager->status == -1) return -1;

	engineManager->loop();

	delete engineManager;

	return 0;
}