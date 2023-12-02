#include <peppermint/managers/InputManager.h>

using namespace peppermint::managers;

peppermint::Window* InputManager::currentWindow = nullptr;

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
	for (unsigned int i = 0; i < sizeof(*keys) / sizeof(const int); i++) {
		if (glfwGetKey(currentWindow->getAddress(), keys[i]) == GLFW_PRESS) return true;
	}
	return false;
}

bool InputManager::active(INPUT_TYPES type, MODIFIERS modifier) {
	if (glfwGetKey(currentWindow->getAddress(), modifier) != GLFW_PRESS) return false;
	return InputManager::active(type);
}

void InputManager::setWindow(Window* win) {
	InputManager::currentWindow = win;
}