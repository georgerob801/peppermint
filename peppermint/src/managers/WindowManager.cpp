#include <iostream>
#include <peppermint-preview/managers/WindowManager.h>

using namespace peppermint;
using namespace peppermint::managers;
using namespace std;

WindowManager::WindowManager() {

}

Window* WindowManager::createWindow() {
	return WindowManager::createWindow(WindowManager::defaultWidth, WindowManager::defaultHeight);
}

Window* WindowManager::createWindow(int width, int height) {
	Window* window = new Window(width, height);
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