#ifndef PPMINT_INPUT_MANAGER_H
#define PPMINT_INPUT_MANAGER_H

#include <peppermint/classes/Window.h>

namespace peppermint {
	namespace managers {
		/// <summary>
		/// Class for handling user input.
		/// </summary>
		class InputManager {
		public:
			/// <summary>
			/// The keys that correspond to the forwards direction.
			/// </summary>
			static constexpr int FORWARD_KEYS[] = {
				GLFW_KEY_W,
				GLFW_KEY_UP
			};

			/// <summary>
			/// The keys that correspond to the backwards direction.
			/// </summary>
			static constexpr int BACKWARD_KEYS[] = {
				GLFW_KEY_S,
				GLFW_KEY_DOWN
			};

			/// <summary>
			/// The keys that correspond to the left direction.
			/// </summary>
			static constexpr int LEFT_KEYS[] = {
				GLFW_KEY_A,
				GLFW_KEY_LEFT
			};

			/// <summary>
			/// The keys that correspond to the right direction.
			/// </summary>
			static constexpr int RIGHT_KEYS[] = {
				GLFW_KEY_D,
				GLFW_KEY_RIGHT
			};

			/// <summary>
			/// The keys that correspond to the up direction.
			/// </summary>
			static constexpr int UP_KEYS[] = {
				GLFW_KEY_E
			};

			/// <summary>
			/// The keys that correspond to the down direction.
			/// </summary>
			static constexpr int DOWN_KEYS[] = {
				GLFW_KEY_Q
			};

			/// <summary>
			/// Enum for determining the type of input.
			/// </summary>
			enum INPUT_TYPES {
				FORWARD,
				BACKWARD,
				LEFT,
				RIGHT,
				UP,
				DOWN
			};

			/// <summary>
			/// Enum for determining modifying keys.
			/// </summary>
			enum MODIFIERS {
				L_CTRL = GLFW_KEY_LEFT_CONTROL,
				R_CTRL = GLFW_KEY_RIGHT_CONTROL,
				L_ALT = GLFW_KEY_LEFT_ALT,
				R_ALT = GLFW_KEY_RIGHT_ALT,
				L_SHIFT = GLFW_KEY_LEFT_SHIFT,
				R_SHIFT = GLFW_KEY_RIGHT_SHIFT
			};

			/// <summary>
			/// Determine whether a certain input type is active.
			/// </summary>
			/// <param name="type">The input type.</param>
			/// <returns>True/false depending on whether the input is active.</returns>
			static bool active(INPUT_TYPES type);
			/// <summary>
			/// Determine whether a certain input type is active.
			/// </summary>
			/// <param name="type">The input type.</param>
			/// <param name="modifier">The input modifier.</param>
			/// <returns>True/false depending on whether the input is active.</returns>
			static bool active(INPUT_TYPES type, MODIFIERS modifier);

			/// <summary>
			/// Set the Window this InputManager is checking for input on.
			/// </summary>
			/// <param name="win">The Window to set.</param>
			static void setWindow(Window* win);
		private:
			/// <summary>
			/// Get the keys that correspond to an input type.
			/// </summary>
			/// <param name="type">The input type to get keys for.</param>
			/// <returns>The keys that correspond to the specified input type.</returns>
			static const int* getKeys(INPUT_TYPES type);
			/// <summary>
			/// A pointer to the Window currently in use.
			/// </summary>
			static Window* currentWindow;
		};
	}
}

#endif