#ifndef PPMINT_ENGINE_MANAGER_H
#define PPMINT_ENGINE_MANAGER_H

#include <vector>

#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/WindowManager.h>
#include <peppermint/managers/WorldManager.h>
#include <peppermint/managers/AssetManager.h>

namespace peppermint {
	namespace managers {
		/// <summary>
		/// Class that manages literally everything.
		/// </summary>
		class EngineManager {
		public:
			// -1 = error has occurred, crash

			/// <summary>
			/// Current status of the EngineManager. Hope that it never goes to -1.
			/// </summary>
			short status = 0;

			/// <summary>
			/// The index of the first WorldManager to load.
			/// </summary>
			static unsigned int initialWorldIndex;

			// open gl properties
			
			/// <summary>
			/// The major version of OpenGL to use.
			/// </summary>
			static const int majorVersion = 3;
			/// <summary>
			/// The minor version of OpenGL to use.
			/// </summary>
			static const int minorVersion = 3;

			/// <summary>
			/// A pointer to the WindowManager to use.
			/// </summary>
			static WindowManager* windowManager;
			/// <summary>
			/// A pointer to the AssetManager to use.
			/// </summary>
			static AssetManager* assetManager;

			/// <summary>
			/// A vector containing all WorldManagers used by this EngineManager.
			/// </summary>
			static std::vector<WorldManager*> worldManagers;
			/// <summary>
			/// The index of the currently active WorldManager.
			/// </summary>
			static unsigned int activeWorldManager;

			/// <summary>
			/// Create a new EngineManager.
			/// </summary>
			EngineManager();
			/// <summary>
			/// Destroy this EngineManager.
			/// </summary>
			~EngineManager();

			/// <summary>
			/// Update the time between frames.
			/// </summary>
			void updateDeltaTime();
			/// <summary>
			/// Get the time since the beginning of this frame.
			/// </summary>
			double vSyncTime();

			/// <summary>
			/// Run the actual engine after setup.
			/// </summary>
			void loop();

			/// <summary>
			/// Go to a specified world.
			/// </summary>
			static void goToWorld(unsigned int worldIndex);

			/// <summary>
			/// Create a new WorldManager.
			/// </summary>
			static WorldManager* createWorldManager();

			/// <summary>
			/// The time between frames.
			/// </summary>
			static double deltaTime;

			/// <summary>
			/// Set the game file Asset of this EngineManager.
			/// </summary>
			static void setGameFile(Asset* gameFile);
			/// <summary>
			/// Load the data from this EngineManager's game file into this EngineManager.
			/// </summary>
			static void loadFromGameFile();
			/// <summary>
			/// Save this EngineManager's game file.
			/// </summary>
			static void saveGameFile();
		private:
			/// <summary>
			/// The time of the last frame.
			/// </summary>
			static double lastFrame;
			/// <summary>
			/// This EngineManager's game file Asset.
			/// </summary>
			static Asset* gameFile; 
		};
	}
}

#endif