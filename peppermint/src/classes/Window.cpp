#include <peppermint/classes/Window.h>

#include <format>

using namespace peppermint;
using namespace peppermint::managers;

void onResize(GLFWwindow* window, int width, int height) {
	glfwMakeContextCurrent(window);
	float offsetX = 0;
	float offsetY = 0;
	float unit;
	if ((float)width / 16.0f < (float)height / 9.0f) {
		unit = (float)width / 16.0f;
		offsetY = (float)height - (9 * unit);
	} else {
		unit = (float)height / 9.0f;
		offsetX = (float)width - (16 * unit);
	}
	glViewport((int)(offsetX / 2.0f), (int)(offsetY / 2.0f), (int)(16 * unit), (int)(9 * unit));
}

Window::Window(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share) {
	status = 0;

	LogManager::debug(std::format("Attempting to create {}x{} window titled '{}'", width, height, title));

	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);

	if (window == NULL) {
		LogManager::critical("Failed to create GLFW window");
		this->status = -1;
	} else {
		LogManager::info(std::format("Created '{}' window successfully at {} for peppermint::Window at {}", title, (void*)window, (void*)this));
	}

	this->glfwWindow = window;
	LogManager::debug(std::format("Creating render manager for {}", (void*)this));
	this->renderManager = new RenderManager();
	LogManager::debug(std::format("Created render manager for {}", (void*)this));

	LogManager::debug(std::format("Setting resize handler for {}", (void*)this));
	onResize(this->glfwWindow, this->getSize()[0], this->getSize()[1]);
	glfwSetFramebufferSizeCallback(this->glfwWindow, onResize);
}

Window::~Window() {
	glfwDestroyWindow(this->glfwWindow);
	delete this->renderManager;
}

void Window::makeCurrentContext() {
	glfwMakeContextCurrent(this->getAddress());
}

GLFWwindow* Window::getAddress() {
	return this->glfwWindow;
}

int* Window::getSize() {
	int size[2] = { 0, 0 };
	glfwGetWindowSize(this->getAddress(), &size[0], &size[1]);
	return size;
}

void Window::swapBuffers() {
	glfwSwapBuffers(this->getAddress());
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(this->getAddress());
}

void Window::renderFrame() {
	this->makeCurrentContext();
	int* size = this->getSize();
	this->renderManager->renderFrame();
}