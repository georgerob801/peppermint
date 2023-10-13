#include <iostream>
#include <peppermint/managers/WindowManager.h>

using namespace peppermint;
using namespace peppermint::managers;
using namespace std;

WindowManager::WindowManager() {

}

Window* WindowManager::createWindow() {
	return WindowManager::createWindow(WindowManager::defaultWidth, WindowManager::defaultHeight, WindowManager::defaultTitle, WindowManager::defaultMonitor, WindowManager::defaultShare);
}

Window* WindowManager::createWindow(int width, int height) {
	return WindowManager::createWindow(width, height, WindowManager::defaultTitle, WindowManager::defaultMonitor, WindowManager::defaultShare);
}

Window* WindowManager::createWindow(int width, int height, char* title) {
	return WindowManager::createWindow(width, height, title, WindowManager::defaultMonitor, WindowManager::defaultShare);
}

Window* WindowManager::createWindow(int width, int height, char* title, GLFWmonitor* monitor, GLFWwindow* share) {
	Window* window = new Window(width, height, title, monitor, share);
	if (window->status == -1) this->status = -1;

	this->windows.push_back(window);

	return window;
}

WindowManager* WindowManager::setCurrentWindow(Window* window) {
	this->currentWindow = window;
	window->makeCurrentContext();
	return this;
}

Window* WindowManager::getWindow() {
	return this->currentWindow;
}