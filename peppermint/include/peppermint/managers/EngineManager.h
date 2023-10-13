#ifndef PPMINT_ENGINE_MANAGER_H
#define PPMINT_ENGINE_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/WindowManager.h>

namespace peppermint {
	namespace managers {
		class EngineManager {
		public:
			// -1 = error has occurred, crash
			short status = 0;

			// open gl properties
			static const int majorVersion = 3;
			static const int minorVersion = 3;

			WindowManager* windowManager;

			EngineManager();
			~EngineManager();
		private:

		};
	}
}

#endif