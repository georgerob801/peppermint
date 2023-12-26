#include <peppermint-preview/classes/Window.h>

#include <format>

#include <peppermint-preview/managers/EngineManager.h>

using namespace peppermint;
using namespace peppermint::managers;

//void onResize(GLFWwindow* window, int width, int height) {
//	glfwMakeContextCurrent(window);
//	float offsetX = 0;
//	float offsetY = 0;
//	float unit;
//	if ((float)width / 16.0f < (float)height / 9.0f) {
//		unit = (float)width / 16.0f;
//		offsetY = (float)height - (9 * unit);
//	} else {
//		unit = (float)height / 9.0f;
//		offsetX = (float)width - (16 * unit);
//	}
//	// glViewport((int)(offsetX / 2.0f), (int)(offsetY / 2.0f), (int)(16 * unit), (int)(9 * unit));
//	glViewport(0, 0, (int)(16 * unit), (int)(9 * unit));
//}

void Window::getIntendedViewportSize(int* thing) {
	int size[2];
	this->getSize(size);
	int width = size[0];
	int height = size[1];
	float unit;
	if ((float)width / 16.0f < (float)height / 9.0f) {
		unit = (float)width / 16.0f;
	} else {
		unit = (float)height / 9.0f;
	}

	thing[0] = (int)(16 * unit);
	thing[1] = (int)(9 * unit);
}

Window::Window(int width, int height) {
	status = 0;

	this->width = width;
	this->height = height;
}

Window::~Window() {
	// glfwDestroyWindow(this->glfwWindow);
	delete this->renderManager;
}

void Window::makeCurrentContext() {
	// glfwMakeContextCurrent(this->getAddress());
}

void Window::getSize(int* thing) {
	thing[0] = this->width;
	thing[1] = this->height;
}

bool Window::shouldClose() {
	return this->shouldCloseV;
}

void Window::setShouldClose(bool val) {
	this->shouldCloseV = val;
}

void Window::renderFrame() {
	this->makeCurrentContext();
	this->renderManager->renderFrame();
}