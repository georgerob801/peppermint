#include <peppermint-preview/managers/InputManager.h>

using namespace peppermint::managers;

peppermint::Window* InputManager::currentWindow = nullptr;
GLFWwindow* InputManager::inputWindow = nullptr;

const int* InputManager::getKeys(INPUT_TYPES type) {
	switch (type) {
	case FORWARD:
		return InputManager::FORWARD_KEYS;
	case BACKWARD:
		return InputManager::BACKWARD_KEYS;
	case LEFT:
		return InputManager::LEFT_KEYS;
	case RIGHT:
		return InputManager::RIGHT_KEYS;
	case UP:
		return InputManager::UP_KEYS;
	case DOWN:
		return InputManager::DOWN_KEYS;
	default:
		return {};
	}
}

// todo: fix this algorithm (pointer size issue)
bool InputManager::active(INPUT_TYPES type) {
	const int* keys = InputManager::getKeys(type);
	for (unsigned int i = 0; i < InputManager::getNumKeys(type); i++) {
		if (glfwGetKey(InputManager::inputWindow, keys[i]) == GLFW_PRESS) return true;
	}
	return false;
}

bool InputManager::active(INPUT_TYPES type, MODIFIERS modifier) {
	if (glfwGetKey(InputManager::inputWindow, modifier) != GLFW_PRESS) return false;
	return InputManager::active(type);
}

void InputManager::setWindow(Window* win) {
	InputManager::currentWindow = win;
}

unsigned int InputManager::getNumKeys(INPUT_TYPES type) {
	switch (type) {
	case FORWARD:
		return InputManager::NUM_KEYS.forward;
	case BACKWARD:
		return InputManager::NUM_KEYS.backward;
	case LEFT:
		return InputManager::NUM_KEYS.left;
	case RIGHT:
		return InputManager::NUM_KEYS.right;
	case UP:
		return InputManager::NUM_KEYS.up;
	case DOWN:
		return InputManager::NUM_KEYS.down;
	default:
		return 0;
	}
}