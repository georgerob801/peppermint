#include <peppermint/classes/Window.h>

using namespace peppermint;
using namespace peppermint::managers;

Window::Window(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share) {
	status = 0;

	LogManager::debug(std::format("Attempting to create {}x{} window titled '{}'", width, height, title));

	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);

	if (window == NULL) {
		LogManager::critical("Failed to create GLFW window");
		this->status = -1;
	} else {
		LogManager::info(std::format("Created '{}' window successfully at {}", title, (void*)window));
	}

	this->glfwWindow = window;
	this->renderManager = new RenderManager();
}

Window::~Window() {
	delete this->renderManager;
}

void Window::makeCurrentContext() {
	glfwMakeContextCurrent(this->getAddress());
}

GLFWwindow* Window::getAddress() {
	return this->glfwWindow;
}

int* Window::getSize() {
	int* size[2] = { 0, 0 };
	glfwGetWindowSize(this->getAddress(), size[0], size[1]);
	return *size;
}

void Window::swapBuffers() {
	glfwSwapBuffers(this->getAddress());
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(this->getAddress());
}