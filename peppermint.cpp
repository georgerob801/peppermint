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

#include <peppermint/classes/rendering/Shader.h>
#include <peppermint/classes/rendering/Mesh.h>

EngineManager* engineManager;

int main() {
	stbi_set_flip_vertically_on_load(true);

	engineManager = new EngineManager();
	if (engineManager->status == -1) return -1;

	Shader* shader = new Shader((char*)"peppermint/resource/shader/vertex/default.vert", (char*)"peppermint/resource/shader/fragment/default.frag");

	Mesh* mesh = new Mesh();

	float testData[] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};

	vector<unsigned int> testIndices = {
		0, 1, 2,
		1, 2, 3
	};

	for (int i = 0; i < 4; i++) {
		rendering::Vertex vert;
		vert.position = vec3(testData[(i * 5) + 0], testData[(i * 5) + 1], testData[(i * 5) + 2]);
		vert.uv = vec2(testData[(i * 5) + 3], testData[(i * 5) + 4]);

		mesh->vertices.push_back(vert);
	}

	mesh->indices = testIndices;

	mesh->setup();

	engineManager->loop();

	delete engineManager;

	return 0;
}