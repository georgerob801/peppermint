#include <peppermint/classes/Window.h>

#include <format>

#include <peppermint/managers/EngineManager.h>

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

	glViewport(0, 0, (int)(16 * unit), (int)(9 * unit));

	vector<Window*>::iterator i = find_if(EngineManager::windowManager->windows.begin(), EngineManager::windowManager->windows.end(), [window](Window* item) { return item->getAddress() == window; });
	if (i != EngineManager::windowManager->windows.end()) {
		// window exists, check for fbo
		if ((*i)->renderManager->FBO != NULL) {
			(*i)->renderManager->resizeFBOAttachments();
		}
	}
}

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
	int size[2];
	this->getSize(size);
	onResize(this->glfwWindow, size[0], size[1]);
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

void Window::getSize(int* thing) {
	glfwGetWindowSize(this->getAddress(), &thing[0], &thing[1]);
}

void Window::swapBuffers() {
	glfwSwapBuffers(this->getAddress());
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(this->getAddress());
}

void Window::renderFrame() {
	this->makeCurrentContext();
	this->renderManager->renderFrame();
}

void Window::setName(const char* name) {
	this->setName((char*)name);
}

void Window::setName(char* name) {
	glfwSetWindowTitle(this->getAddress(), name);
}