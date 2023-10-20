#include <peppermint/managers/RenderManager.h>

#include <peppermint/classes/Window.h>

using namespace peppermint;
using namespace peppermint::managers;

RenderManager::RenderManager() {
	this->backgroundColour = vec4(0.0f, 1.0f, 0.4f, 1.0f);

	glEnable(GL_CULL_FACE);
}

RenderManager::~RenderManager() {
	
}

void RenderManager::setCamera(Camera* cam) {
	this->activeCamera = cam;
}

void RenderManager::renderFrame() {
	glClearColor(this->backgroundColour.x, this->backgroundColour.y, this->backgroundColour.z, this->backgroundColour.z);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}