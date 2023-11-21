#ifndef PPMINT_COMPONENT_WARP_TILE
#define PPMINT_COMPONENT_WARP_TILE

#include <peppermint/classes/game/Component.h>
#include <glm/glm.hpp>

using namespace glm;

namespace peppermint {
	namespace game {
		namespace components {
			class WarpTile : public Component {
			public:
				WarpTile() {
					this->type = Component::WARP_TILE;
				}

				unsigned int destinationWorld = NULL;

				enum Facing {
					UP,
					DOWN,
					LEFT,
					RIGHT
				};

				bool requiresFacing = false;
				Facing facingToGo;

				Facing facingAtDestination;

				vec3 destinationCharacterPosition = vec3(0, 0, 0);

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			};

		}
	}
}
#endif