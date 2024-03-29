#ifndef PPMINT_ENGINE_MANAGER_H
#define PPMINT_ENGINE_MANAGER_H

#include <vector>

#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/WindowManager.h>
#include <peppermint/managers/WorldManager.h>
#include <peppermint/managers/AssetManager.h>
#include <peppermint/managers/SoundManager.h>

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
			static short status;

			/// <summary>
			/// The index of the first WorldManager to load.
			/// </summary>
			static unsigned int initialWorldIndex;

			// open gl properties
			
			/// <summary>
			/// The major version of OpenGL to use.
			/// </summary>
			static const int majorVersion = 4;
			/// <summary>
			/// The minor version of OpenGL to use.
			/// </summary>
			static const int minorVersion = 6;

			/// <summary>
			/// A pointer to the WindowManager to use.
			/// </summary>
			static WindowManager* windowManager;
			/// <summary>
			/// A pointer to the AssetManager to use.
			/// </summary>
			static AssetManager* assetManager;
			/// <summary>
			/// A pointer to the SoundManager to use.
			/// </summary>
			static SoundManager* soundManager;

			/// <summary>
			/// A vector containing all WorldManagers used by this EngineManager.
			/// </summary>
			static std::vector<WorldManager*> worldManagers;
			/// <summary>
			/// The index of the currently active WorldManager.
			/// </summary>
			static unsigned int activeWorldManager;

			/// <summary>
			/// Determine whether this should actually output anything to a screen.
			/// </summary>
			static bool outputToScreen;

			/// <summary>
			/// Create a new EngineManager.
			/// </summary>
			EngineManager();
			static void initialise();
			/// <summary>
			/// Destroy this EngineManager.
			/// </summary>
			~EngineManager();
			static void destroy();

			/// <summary>
			/// Update the time between frames.
			/// </summary>
			static void updateDeltaTime();
			/// <summary>
			/// Get the time since the beginning of this frame.
			/// </summary>
			static double vSyncTime();

			/// <summary>
			/// Run the actual engine after setup.
			/// </summary>
			static void loop();

			/// <summary>
			/// Go to a specified world.
			/// </summary>
			static void goToWorld(unsigned int worldIndex);

			/// <summary>
			/// Get the current WorldManager.
			/// </summary>
			/// <returns>The current WorldManager</returns>
			static WorldManager* getWM();

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
			/// <summary>
			/// Saves everything that needs saving.
			/// </summary>
			static void saveAll();
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