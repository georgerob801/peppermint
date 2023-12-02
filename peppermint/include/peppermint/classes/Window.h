#ifndef PPMINT_WINDOW_H
#define PPMINT_WINDOW_H

#include <GLFW/glfw3.h>
#include <format>
#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/RenderManager.h>

namespace peppermint {
	/// <summary>
	/// Class for storing information about windows.
	/// </summary>
	class Window {
	public:
		/// <summary>
		/// Create a new Window.
		/// </summary>
		/// <param name="width">The desired width of the window.</param>
		/// <param name="height">The desired height of the window.</param>
		/// <param name="title">The desired title of the window.</param>
		/// <param name="monitor">Which monitor to display the window on.</param>
		/// <param name="share">Can't remember what this does lmao</param>
		Window(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share);
		/// <summary>
		/// Destroy this Window.
		/// </summary>
		~Window();

		/// <summary>
		/// The current status of this Window.
		/// </summary>
		int status;
		/// <summary>
		/// A pointer to this Window's RenderManager.
		/// </summary>
		managers::RenderManager* renderManager;

		/// <summary>
		/// Get a pointer to this Window's GLFWwindow.
		/// </summary>
		/// <returns>A pointer to this Window's GLFWwindow.</returns>
		GLFWwindow* getAddress();
		/// <summary>
		/// Make this Window the current context.
		/// </summary>
		void makeCurrentContext();

		/// <summary>
		/// Get the size of this Window.
		/// </summary>
		/// <param name="thing">Pointer to the location to write the width and height in.</param>
		void getSize(int* thing);

		/// <summary>
		/// Swap this Window's buffers.
		/// </summary>
		void swapBuffers();
		/// <summary>
		/// Determine whether this Window should close.
		/// </summary>
		/// <returns>True/false depending on whether this Window should close.</returns>
		bool shouldClose();

		/// <summary>
		/// Render the next frame.
		/// </summary>
		void renderFrame();

		/// <summary>
		/// Set this Window's name.
		/// </summary>
		/// <param name="name">The name to set.</param>
		void setName(const char* name);
		/// <summary>
		/// Set this Window's name.
		/// </summary>
		/// <param name="name">The name to set.</param>
		void setName(char* name);
	private:
		/// <summary>
		/// This Window's GLFWwindow.
		/// </summary>
		GLFWwindow* glfwWindow;
	};
}

#endif