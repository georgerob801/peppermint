#ifndef PPMINT_GAME_OBJECT_H
#define PPMINT_GAME_OBJECT_H

#include <vector>
#include <peppermint/classes/game/Component.h>
#include <peppermint/classes/game/components/Transform.h>

using namespace peppermint::game::components;

namespace peppermint {
	namespace game {
		class GameObject {
		public:
			Transform* transform;

			std::vector<Component*> components;

			GameObject();
			~GameObject();

			template<class c> Component* addComponent();

			template<class c> Component* getComponent();
		private:

		};
	}
}

#endif