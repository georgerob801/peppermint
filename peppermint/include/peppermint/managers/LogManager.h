#ifndef PPMINT_LOG_MANAGER_H
#define PPMINT_LOG_MANAGER_H

#include <iostream>
#include <chrono>

namespace peppermint {
	namespace managers {
		class LogManager {
		public:
			static void debug(std::string message);
			static void info(std::string message);
			static void warn(std::string message);
			static void error(std::string message);
			static void critical(std::string message);

			struct enabledLevels {
				static const bool debug = true;
				static const bool info = true;
				static const bool warn = true;
				static const bool error = true;
				static const bool critical = true;
			};

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
			static const char* colourToEscape(COLOURS colour);
		};
	}
}

#endif