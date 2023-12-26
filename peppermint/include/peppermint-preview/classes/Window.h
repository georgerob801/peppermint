#ifndef PPMINT_WINDOW_H
#define PPMINT_WINDOW_H

#include <format>
#include <peppermint-preview/managers/LogManager.h>
#include <peppermint-preview/managers/RenderManager.h>

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
		Window(int width, int height);
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
		/// Make this Window the current context.
		/// </summary>
		void makeCurrentContext();

		/// <summary>
		/// Get the size of this Window.
		/// </summary>
		/// <param name="thing">Pointer to the location to write the width and height in.</param>
		void getSize(int* thing);

		/// <summary>
		/// Get the current size the viewport should be.
		/// </summary>
		/// <param name="thing"></param>
		void getIntendedViewportSize(int* thing);

		/// <summary>
		/// Determine whether this Window should close.
		/// </summary>
		/// <returns>True/false depending on whether this Window should close.</returns>
		bool shouldClose();

		/// <summary>
		/// Render the next frame.
		/// </summary>
		void renderFrame();

		void setShouldClose(bool val);

		int width = 0;
		int height = 0;
	private:
		/// <summary>
		/// This Window's GLFWwindow.
		/// </summary>
		// GLFWwindow* glfwWindow;


		bool shouldCloseV = false;
	};
}

#endif