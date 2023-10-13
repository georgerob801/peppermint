#ifndef PPMINT_WINDOW_H
#define PPMINT_WINDOW_H

#include <GLFW/glfw3.h>
#include <format>
#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/RenderManager.h>

namespace peppermint {
	class Window {
	public:
		Window(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share);
		~Window();

		int status;
		managers::RenderManager* renderManager;

		GLFWwindow* getAddress();
		void makeCurrentContext();

		int* getSize();

		void swapBuffers();
		bool shouldClose();
	private:
		GLFWwindow* glfwWindow;
	};
}

#endif