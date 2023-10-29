#ifndef PPMINT_WORLD_MANAGER_H
#define PPMINT_WORLD_MANAGER_H

#include <vector>
#include <peppermint/classes/game/GameObject.h>
#include <peppermint/classes/game/components/Camera.h>
#include <peppermint/classes/Window.h>

using namespace peppermint::game;

namespace peppermint {
	namespace managers {
		class WorldManager {
		public:
			std::vector<GameObject*> gameObjects;

			Shader* shader = new Shader((char*)"peppermint/resource/shader/vertex/default.vert", (char*)"peppermint/resource/shader/fragment/default.frag");

			void awake();
			void start();
			void loop(Window* window);

			void sortByZ();

			GameObject* createGameObject();
		private:
			
		};
	}
}

#endif