#include <peppermint/managers/RenderManager.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <peppermint/classes/Window.h>
#include <peppermint/managers/EngineManager.h>

using namespace peppermint;
using namespace peppermint::managers;

RenderManager::RenderManager() {
	this->backgroundColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->activeRenderQueue = new RenderQueue();
	this->activeCamera = nullptr;
	this->status = 0;
	this->FBO = NULL;
}

RenderManager::~RenderManager() {
	if (this->FBO != NULL) {
		glDeleteFramebuffers(1, &this->FBO);
		glDeleteTextures(1, &this->colourTex);
		glDeleteRenderbuffers(1, &this->RBO);
	}
}

void RenderManager::unbindFBOs() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int RenderManager::getColourTex() {
	return this->colourTex;
}

void RenderManager::resizeFBOAttachments() {
	if (this->FBO != NULL) {
		Window* win = EngineManager::windowManager->getWindow();

		int size[2];
		win->getIntendedViewportSize(size);

		glBindTexture(GL_TEXTURE_2D, this->colourTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size[0], size[1], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glBindTexture(GL_TEXTURE_2D, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0);

		glDeleteRenderbuffers(1, &this->RBO);

		glGenRenderbuffers(1, &this->RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size[0], size[1]);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->RBO);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void RenderManager::setupFBO() {
	this->screenShader = new Shader(new Asset(Asset::VERTEX_SHADER_SOURCE, (char*)"peppermint/resource/shader/vertex/screen.vert"), new Asset(Asset::FRAGMENT_SHADER_SOURCE, (char*)"peppermint/resource/shader/fragment/screen.frag"));

	if (this->FBO == NULL) {
		LogManager::debug(format("Creating new FBO for RenderManager at {}", (void*)this));
		glGenFramebuffers(1, &this->FBO);
		LogManager::debug(format("Created new FBO at {}", this->FBO));
	}

	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);

	Window* win = EngineManager::windowManager->getWindow();

	int size[2];
	win->getSize(size);

	// colour texture
	glGenTextures(1, &this->colourTex);
	glBindTexture(GL_TEXTURE_2D, this->colourTex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size[0], size[1], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColour[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colourTex, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	// RBO (depth/stencil)
	glGenRenderbuffers(1, &this->RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size[0], size[1]);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->RBO);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) LogManager::critical("Could not set up FBO correctly");
	else LogManager::debug("FBO set up correctly");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glGenVertexArrays(1, &this->fboVAO);
	glBindVertexArray(this->fboVAO);

	glGenBuffers(1, &this->fboVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->fboVBO);

	float vertices[24] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void RenderManager::bindFBO() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
}

void RenderManager::setCamera(Camera* cam) {
	this->activeCamera = cam;
}

void RenderManager::renderFrame() {
	if (this->FBO != NULL) this->bindFBO();
	glClearColor(this->backgroundColour.x, this->backgroundColour.y, this->backgroundColour.z, this->backgroundColour.z);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	while (this->activeRenderQueue->renderItems.size() != 0) {
		// ignore if from wrong world (eg last frame before a world change)
		if (this->activeRenderQueue->renderItems[0].fromWorld != EngineManager::worldManagers[EngineManager::activeWorldManager]) {
			this->activeRenderQueue->renderItems.erase(this->activeRenderQueue->renderItems.begin());
			continue;
		}

		this->activeRenderQueue->renderItems[0].shader->use();
		this->activeRenderQueue->renderItems[0].shader->setMat4f((char*)"model", this->activeRenderQueue->renderItems[0].go->transform->getMatrix());
		this->activeRenderQueue->renderItems[0].shader->setMat4f((char*)"view", this->activeCamera->getViewMatrix());
		float* scale = &this->activeCamera->viewScale;

		this->activeRenderQueue->renderItems[0].shader->setMat4f((char*)"projection", /*perspective(glm::quarter_pi<float>(), 16.0f / 9.0f, 0.1f, 100.0f)); */ ortho(-8.0f * *scale, 8.0f * *scale, -4.5f * *scale, 4.5f * *scale, 0.1f, 100.0f));

		this->activeRenderQueue->renderItems[0].shader->setVec3f((char*)"vertexColour", this->activeRenderQueue->renderItems[0].mesh->vertColour);
		this->activeRenderQueue->renderItems[0].shader->setInt((char*)"material.useTexture", this->activeRenderQueue->renderItems[0].textureToUse);
		this->activeRenderQueue->renderItems[0].shader->setVec2f((char*)"material.offset", this->activeRenderQueue->renderItems[0].uvOffset);

		this->activeRenderQueue->renderItems[0].mesh->draw(this->activeRenderQueue->renderItems[0].shader);
		this->activeRenderQueue->renderItems.erase(this->activeRenderQueue->renderItems.begin());
	}

	if (this->FBO != NULL) {
		int viewportData[4];
		glGetIntegerv(GL_VIEWPORT, &viewportData[0]);
		RenderManager::unbindFBOs();

		int winSize[2];
		EngineManager::windowManager->getWindow()->getSize(winSize);
		int viewSize[2];
		EngineManager::windowManager->getWindow()->getIntendedViewportSize(viewSize);
		glViewport((int)((winSize[0] - viewSize[0]) / 2), (int)((winSize[1] - viewSize[1]) / 2), viewSize[0], viewSize[1]);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		this->screenShader->use();
		this->screenShader->setInt((char*)"screenTexture", 0);
		glBindVertexArray(this->fboVAO);
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->colourTex);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glViewport(viewportData[0], viewportData[1], viewportData[2], viewportData[3]);
	}
}