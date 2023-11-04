#ifndef PPMINT_ENGINE_MANAGER_H
#define PPMINT_ENGINE_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/WindowManager.h>
#include <peppermint/managers/WorldManager.h>
#include <peppermint/managers/AssetManager.h>

namespace peppermint {
	namespace managers {
		class EngineManager {
		public:
			// -1 = error has occurred, crash
			short status = 0;

			// open gl properties
			static const int majorVersion = 3;
			static const int minorVersion = 3;

			static WindowManager* windowManager;
			static AssetManager* assetManager;

			std::vector<WorldManager*> worldManagers;
			int activeWorldManager = NULL;

			EngineManager();
			~EngineManager();

			void updateDeltaTime();
			double vSyncTime();

			void loop();

			static double deltaTime;
		private:
			static double lastFrame;
		};
	}
}

#endif