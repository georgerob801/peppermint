#ifndef PPMINT_INPUT_MANAGER_H
#define PPMINT_INPUT_MANAGER_H

#include <peppermint/classes/Window.h>

namespace peppermint {
	namespace managers {
		class InputManager {
		public:
			static constexpr int FORWARD_KEYS[] = {
				GLFW_KEY_W,
				GLFW_KEY_UP
			};

			static constexpr int BACKWARD_KEYS[] = {
				GLFW_KEY_S,
				GLFW_KEY_DOWN
			};

			static constexpr int LEFT_KEYS[] = {
				GLFW_KEY_A,
				GLFW_KEY_LEFT
			};

			static constexpr int RIGHT_KEYS[] = {
				GLFW_KEY_D,
				GLFW_KEY_RIGHT
			};

			static constexpr int UP_KEYS[] = {
				GLFW_KEY_E
			};

			static constexpr int DOWN_KEYS[] = {
				GLFW_KEY_Q
			};

			enum INPUT_TYPES {
				FORWARD,
				BACKWARD,
				LEFT,
				RIGHT,
				UP,
				DOWN
			};

			enum MODIFIERS {
				L_CTRL = GLFW_KEY_LEFT_CONTROL,
				R_CTRL = GLFW_KEY_RIGHT_CONTROL,
				L_ALT = GLFW_KEY_LEFT_ALT,
				R_ALT = GLFW_KEY_RIGHT_ALT,
				L_SHIFT = GLFW_KEY_LEFT_SHIFT,
				R_SHIFT = GLFW_KEY_RIGHT_SHIFT
			};

			static bool active(INPUT_TYPES type);
			static bool active(INPUT_TYPES type, MODIFIERS modifier);
			static bool active(INPUT_TYPES type, MODIFIERS* modifiers);

			static void setWindow(Window* win);
		private:
			static const int* getKeys(INPUT_TYPES type);
			static Window* currentWindow;
		};
	}
}

#endif