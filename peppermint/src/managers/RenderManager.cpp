#include <peppermint/managers/RenderManager.h>

#include <peppermint/classes/Window.h>
#include <peppermint/managers/EngineManager.h>

using namespace peppermint;
using namespace peppermint::managers;

RenderManager::RenderManager() {
	this->backgroundColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->activeRenderQueue = new RenderQueue();
	this->activeCamera = nullptr;
}

RenderManager::~RenderManager() {

}

void RenderManager::setCamera(Camera* cam) {
	this->activeCamera = cam;
}

void RenderManager::renderFrame() {
	glClearColor(this->backgroundColour.x, this->backgroundColour.y, this->backgroundColour.z, this->backgroundColour.z);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	while (this->activeRenderQueue->renderItems.size() != 0) {
		// ignore if from wrong world (eg last frame before a world change)
		if (this->activeRenderQueue->renderItems[0].fromWorld != EngineManager::worldManagers[EngineManager::activeWorldManager]) {
			this->activeRenderQueue->renderItems.erase(this->activeRenderQueue->renderItems.begin());
			continue;
		}

		this->activeRenderQueue->renderItems[0].shader->setMat4f((char*)"model", this->activeRenderQueue->renderItems[0].go->transform->getMatrix());
		this->activeRenderQueue->renderItems[0].shader->setMat4f((char*)"view", this->activeCamera->getViewMatrix());
		float* scale = &this->activeCamera->viewScale;
		this->activeRenderQueue->renderItems[0].shader->setMat4f((char*)"projection", /*perspective(glm::quarter_pi<float>(), 16.0f / 9.0f, 0.1f, 100.0f)); */ ortho(-8.0f * *scale, 8.0f * *scale, -4.5f * *scale, 4.5f * *scale, 0.1f, 100.0f));

		this->activeRenderQueue->renderItems[0].shader->setInt((char*)"material.useTexture", this->activeRenderQueue->renderItems[0].textureToUse);
		this->activeRenderQueue->renderItems[0].shader->setVec2f((char*)"material.offset", this->activeRenderQueue->renderItems[0].uvOffset);
		this->activeRenderQueue->renderItems[0].mesh->draw(this->activeRenderQueue->renderItems[0].shader);
		this->activeRenderQueue->renderItems.erase(this->activeRenderQueue->renderItems.begin());
	}
}