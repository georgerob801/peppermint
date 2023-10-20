#ifndef PPMINT_WORLD_MANAGER_H
#define PPMINT_WORLD_MANAGER_H

#include <vector>
#include <peppermint/classes/game/GameObject.h>
#include <peppermint/classes/game/components/Camera.h>

using namespace peppermint::game;

namespace peppermint {
	namespace managers {
		class WorldManager {
		public:
			std::vector<GameObject> gameObjects;

			void awake();
			void start();
			void loop();
		private:

		};
	}
}

#endif