#ifndef PPMINT_ENGINE_MANAGER_H
#define PPMINT_ENGINE_MANAGER_H

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

			static std::vector<WorldManager*> worldManagers;
			static unsigned int activeWorldManager;

			EngineManager();
			~EngineManager();

			void updateDeltaTime();
			double vSyncTime();

			void loop();

			static void goToWorld(unsigned int worldIndex);

			static WorldManager* createWorldManager();

			static double deltaTime;
		private:
			static double lastFrame;
		};
	}
}

#endif