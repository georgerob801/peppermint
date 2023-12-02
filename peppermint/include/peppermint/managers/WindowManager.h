#ifndef PPMINT_WINDOW_MANAGER_H
#define PPMINT_WINDOW_MANAGER_H

#include <vector>
#include <GLFW/glfw3.h>
#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/RenderManager.h>
#include <peppermint/classes/Window.h>

namespace peppermint {
	namespace managers {
		/// <summary>
		/// Class for managing windows.
		/// </summary>
		class WindowManager {
		public:
			// status for errors

			/// <summary>
			/// This WindowManager's current status.
			/// </summary>
			int status = 0;

			/// <summary>
			/// A vector containing pointers to all the Windows in use by this WindowManager.
			/// </summary>
			std::vector<Window*> windows;

			// default window settings

			/// <summary>
			/// Default window width.
			/// </summary>
			int defaultWidth = 800;
			/// <summary>
			/// Default window height.
			/// </summary>
			int defaultHeight = 450;
			/// <summary>
			/// Default window title.
			/// </summary>
			char* defaultTitle = (char*)"peppermint window";
			/// <summary>
			/// Default monitor.
			/// </summary>
			GLFWmonitor* defaultMonitor = NULL;
			/// <summary>
			/// Default share.
			/// </summary>
			GLFWwindow* defaultShare = NULL;

			/// <summary>
			/// Create a new WindowManager.
			/// </summary>
			WindowManager();
			/// <summary>
			/// Create a new Window.
			/// </summary>
			/// <returns>A pointer to the new Window.</returns>
			Window* createWindow();
			/// <summary>
			/// Create a new Window.
			/// </summary>
			/// <param name="width">The width of the window.</param>
			/// <param name="height">The height of the window.</param>
			/// <returns>A pointer to the new Window.</returns>
			Window* createWindow(int width, int height);
			/// <summary>
			/// Create a new Window.
			/// </summary>
			/// <param name="width">The width of the window.</param>
			/// <param name="height">The height of the window.</param>
			/// <param name="title">The title of the window.</param>
			/// <returns>A pointer to the new Window.</returns>
			Window* createWindow(int width, int height, char* title);
			/// <summary>
			/// Create a new Window.
			/// </summary>
			/// <param name="width">The width of the window.</param>
			/// <param name="height">The height of the window.</param>
			/// <param name="title">The title of the window.</param>
			/// <param name="monitor">The monitor to display the window on.</param>
			/// <param name="share">Still can't remember what this does.</param>
			/// <returns>A pointer to the new Window.</returns>
			Window* createWindow(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share);
			/// <summary>
			/// Set the Window currently being processed.
			/// </summary>
			/// <param name="window">A pointer to the window to set.</param>
			/// <returns>A pointer to this WindowManager.</returns>
			WindowManager* setCurrentWindow(Window* window);
			/// <summary>
			/// Get the Window currently being processed.
			/// </summary>
			/// <returns>A pointer to the Window currently being processed.</returns>
			Window* getWindow();
			/// <summary>
			/// True/false depending on whether this WindowManager has any windows left open.
			/// </summary>
			bool hasOpenWindow;
		private:
			/// <summary>
			/// A pointer to the window currently being processed.
			/// </summary>
			Window* currentWindow = NULL;
		};
	}
}

#endif