#ifndef PPMINT_WINDOW_MANAGER_H
#define PPMINT_WINDOW_MANAGER_H

#include <vector>
#include <GLFW/glfw3.h>
#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/RenderManager.h>
#include <peppermint/classes/Window.h>

namespace peppermint {
	namespace managers {
		class WindowManager {
		public:
			// status for errors
			int status = 0;

			std::vector<Window*> windows;

			// default window settings
			int defaultWidth = 500;
			int defaultHeight = 500;
			char* defaultTitle = (char*)"peppermint window";
			GLFWmonitor* defaultMonitor = NULL;
			GLFWwindow* defaultShare = NULL;

			WindowManager();
			Window* createWindow();
			Window* createWindow(int width, int height);
			Window* createWindow(int width, int height, char* title);
			Window* createWindow(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share);
			WindowManager* setCurrentWindow(Window* window);
			Window* getWindow();
			bool hasOpenWindow;
		private:
			Window* currentWindow = NULL;
		};
	}
}

#endif