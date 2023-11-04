#ifndef PPMINT_GAME_OBJECT_H
#define PPMINT_GAME_OBJECT_H

#include <vector>
#include <peppermint/classes/game/Component.h>
#include <peppermint/classes/game/components/Transform.h>
#include <peppermint/Serialisable.h>

using namespace peppermint::game::components;

namespace peppermint {
	namespace game {
		class GameObject : public Serialisable {
		public:
			Transform* transform;

			std::vector<Component*> components;

			GameObject();
			~GameObject();

			template<class T> Component* addComponent();

			template<class T> Component* getComponent();

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
		private:

		};
	}
}

#endif