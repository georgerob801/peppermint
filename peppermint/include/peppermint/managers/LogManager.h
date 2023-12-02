#ifndef PPMINT_LOG_MANAGER_H
#define PPMINT_LOG_MANAGER_H

#include <iostream>
#include <chrono>

namespace peppermint {
	namespace managers {
		/// <summary>
		/// Class for logging messages.
		/// </summary>
		class LogManager {
		public:
			/// <summary>
			/// Send a debug message.
			/// </summary>
			/// <param name="message">The message to send.</param>
			static void debug(std::string message);
			/// <summary>
			/// Send an info message.
			/// </summary>
			/// <param name="message">The message to send.</param>
			static void info(std::string message);
			/// <summary>
			/// Send a warning message.
			/// </summary>
			/// <param name="message">The message to send.</param>
			static void warn(std::string message);
			/// <summary>
			/// Send an error message.
			/// </summary>
			/// <param name="message">The message to send.</param>
			static void error(std::string message);
			/// <summary>
			/// Send a critical error message.
			/// </summary>
			/// <param name="message">The message to send.</param>
			static void critical(std::string message);

			/// <summary>
			/// Struct containing information about which messages to send.
			/// </summary>
			struct enabledLevels {
				static const bool debug = true;
				static const bool info = true;
				static const bool warn = true;
				static const bool error = true;
				static const bool critical = true;
			};

			/// <summary>
			/// Enum for determing the colour of logged text.
			/// </summary>
			enum COLOURS {
				RESET,
				BLACK,
				RED,
				GREEN,
				YELLOW,
				BLUE,
				MAGENTA,
				CYAN,
				WHITE,
				BRIGHT_BLACK,
				BRIGHT_RED,
				BRIGHT_GREEN,
				BRIGHT_YELLOW,
				BRIGHT_BLUE,
				BRIGHT_MAGENTA,
				BRIGHT_CYAN,
				BRIGHT_WHITE
			};
		private:
			/// <summary>
			/// Convert a colour to its respective escape characters.
			/// </summary>
			/// <param name="colour">The colour to get.</param>
			/// <returns>The escape characters.</returns>
			static const char* colourToEscape(COLOURS colour);
		};
	}
}

#endif