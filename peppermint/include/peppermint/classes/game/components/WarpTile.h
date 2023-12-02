#ifndef PPMINT_COMPONENT_WARP_TILE
#define PPMINT_COMPONENT_WARP_TILE

#include <peppermint/classes/game/Component.h>
#include <glm/glm.hpp>

using namespace glm;

namespace peppermint {
	namespace game {
		namespace components {
			/// <summary>
			/// Component for warping things between worlds.
			/// </summary>
			class WarpTile : public Component {
			public:
				/// <summary>
				/// Create a new WarpTile component.
				/// </summary>
				WarpTile() {
					this->type = Component::WARP_TILE;
				}

				/// <summary>
				/// The index of the world this tile will send things to.
				/// </summary>
				unsigned int destinationWorld = NULL;

				/// <summary>
				/// Enum for determining the direction something's facing in.
				/// </summary>
				enum Facing {
					UP,
					DOWN,
					LEFT,
					RIGHT
				};

				/// <summary>
				/// Whether or not things have to be facing a certain way to use this warp tile.
				/// </summary>
				bool requiresFacing = false;
				/// <summary>
				/// The direction things have to face in to use this warp tile.
				/// </summary>
				Facing facingToGo;

				/// <summary>
				/// The direction things will be facing in the world they get transported to.
				/// </summary>
				Facing facingAtDestination;

				/// <summary>
				/// The position things will end up in in the world they get transported to.
				/// </summary>
				vec3 destinationCharacterPosition = vec3(0, 0, 0);

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			};

		}
	}
}
#endif