#ifndef PPMINT_WORLD_MANAGER_H
#define PPMINT_WORLD_MANAGER_H

#include <vector>
#include <peppermint-preview/classes/game/GameObject.h>
#include <peppermint-preview/classes/game/components/Camera.h>
#include <peppermint-preview/classes/Window.h>
#include <peppermint-preview/Serialisable.h>

using namespace peppermint::game;

namespace peppermint {
	namespace managers {
		/// <summary>
		/// Class for managing an individual world.
		/// </summary>
		class WorldManager : public Serialisable {
		public:
			/// <summary>
			/// Create a new WorldManager.
			/// </summary>
			WorldManager();
			/// <summary>
			/// Create a new WorldManager.
			/// </summary>
			/// <param name="filePath">The path to save this world at.</param>
			WorldManager(char* filePath);

			/// <summary>
			/// Destroy this WorldManager.
			/// </summary>
			~WorldManager();

			/// <summary>
			/// A vector containing poitner to all GameObjects used by this WorldManager.
			/// </summary>
			std::vector<GameObject*> gameObjects;

			/// <summary>
			/// A pointer to the Shader used by all objects in this world.
			/// </summary>
			Shader* shader = new Shader(new Asset(Asset::VERTEX_SHADER_SOURCE, (char*)"peppermint/resource/shader/vertex/default.vert"), new Asset(Asset::FRAGMENT_SHADER_SOURCE, (char*)"peppermint/resource/shader/fragment/default.frag"));

			/// <summary>
			/// Runs once when the world starts.
			/// </summary>
			void awake();
			/// <summary>
			/// Runs every frame - runs the start function of components that are yet to run it.
			/// </summary>
			void start();
			/// <summary>
			/// Runs every frame - handles world processing and RenderQueue population.
			/// </summary>
			/// <param name="window">The window to process this WorldManager on.</param>
			void loop(Window* window);

			/// <summary>
			/// Sort all objects in this WorldManager by their Z coordinate (non-thorough fix for z coord transparency errors)
			/// </summary>
			void sortByZ();

			/// <summary>
			/// Create and register a new GameObject.
			/// </summary>
			/// <returns>A pointer to the new GameObject.</returns>
			GameObject* createGameObject();

			/// <summary>
			/// Save a world file.
			/// </summary>
			void saveWorldFile();

			/// <summary>
			/// Load a world file.
			/// </summary>
			void loadWorldFile();

			/// <summary>
			/// Initialise this WorldManager from its world file.
			/// </summary>
			void initialiseFromWorldFile();

			/// <summary>
			/// Pointer to a vector of pointers to all assets used by this game.
			/// </summary>
			vector<Asset*>* assets;

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);

			/// <summary>
			/// Get the first Camera component in this WorldManager.
			/// </summary>
			/// <returns>A pointer to the first Camera component found.</returns>
			Camera* getFirstCamera();

			/// <summary>
			/// Get the first component of any type within this WorldManager.
			/// </summary>
			/// <typeparam name="T">The type of the Component to get.</typeparam>
			/// <returns>A pointer to the found component.</returns>
			template<class T> T* getFirstComponent() {
				for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
					for (unsigned int j = 0; j < this->gameObjects[i]->components.size(); j++) {
						T* test = dynamic_cast<T*>(this->gameObjects[i]->components[j]);
						if (test) return test;
					}
				}
				return nullptr;
			}

			/// <summary>
			/// Set the world file Asset of this WorldManager.
			/// </summary>
			/// <param name="item"></param>
			void setWorldFileAsset(Asset* item);
			/// <summary>
			/// Unload this WorldManager.
			/// </summary>
			void unload();

			/// <summary>
			/// True/false depending on whether this WorldManager has been initialised.
			/// </summary>
			bool initialised = false;
			/// <summary>
			/// True/false depending on whether this WorldManager should stop being processed.
			/// </summary>
			bool stopProcessingWorld = false;
			/// <summary>
			/// A pointer to this WorldManager's world file Asset.
			/// </summary>
			Asset* worldAsset;
		private:

		};
	}
}

#endif