#ifndef PPMINT_WORLD_MANAGER_H
#define PPMINT_WORLD_MANAGER_H

#include <vector>
#include <peppermint/classes/game/GameObject.h>
#include <peppermint/classes/game/components/Camera.h>
#include <peppermint/classes/Window.h>
#include <peppermint/Serialisable.h>

using namespace peppermint::game;

namespace peppermint {
	namespace managers {
		class WorldManager : public Serialisable {
		public:
			WorldManager();
			WorldManager(char* filePath);

			std::vector<GameObject*> gameObjects;

			Shader* shader = new Shader((char*)"peppermint/resource/shader/vertex/default.vert", (char*)"peppermint/resource/shader/fragment/default.frag");

			void awake();
			void start();
			void loop(Window* window);

			void sortByZ();

			GameObject* createGameObject();

			void saveWorldFile(char* filename);
			void saveWorldFile(const char* filename);

			void loadWorldFile(char* filename);
			void loadWorldFile(const char* filename);

			void initialiseFromWorldFile();

			vector<Asset*>* assets;

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
			Camera* getFirstCamera();

			template<class T> T* getFirstComponent() {
				for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
					for (unsigned int j = 0; j < this->gameObjects[i]->components.size(); j++) {
						T* test = dynamic_cast<T*>(this->gameObjects[i]->components[j]);
						if (test) return test;
					}
				}
				return nullptr;
			}

			void setWorldFileAsset(Asset* item);
			void unload();

			bool initialised = false;
			bool stopProcessingWorld = false;
		private:
			Asset* filePath;
		};
	}
}

#endif