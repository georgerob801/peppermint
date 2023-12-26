#ifndef PPMINT_COMPONENT_PLAYER_CONTROLLER_H
#define PPMINT_COMPONENT_PLAYER_CONTROLLER_H

#include <peppermint-preview/classes/game/Component.h>
#include <peppermint-preview/classes/game/components/NavigableMap.hpp>

#include <glm/glm.hpp>

using namespace glm;

/// <summary>
/// Struct containing data about which keys are currently being pressed.
/// </summary>
struct currentlyPressingStruct {
	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;
};

/// <summary>
/// Struct containing data about which direction a player is currently moving in.
/// </summary>
struct currentlyMovingStruct {
	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;
};

namespace peppermint {
	namespace game {
		namespace components {
			/// <summary>
			/// Component that implements basic control of a player.
			/// </summary>
			class PlayerController : public Component {
			public:
				/// <summary>
				/// Create a new PlayerController.
				/// </summary>
				PlayerController() {
					this->type = Component::PLAYER_CONTROLLER;
				}

				/// <summary>
				/// The movement speed of this player.
				/// </summary>
				float speed = 5.0f;
				/// <summary>
				/// The range within which a player will snap to the nearest tile.
				/// </summary>
				float snapRange = 0.001f;

				/// <summary>
				/// Struct containing data on which keys are currently being pressed.
				/// </summary>
				currentlyPressingStruct currentlyPressing;
				/// <summary>
				/// Struct containing data on which direction this player is currently moving in.
				/// </summary>
				currentlyMovingStruct currentlyMoving;

				/// <summary>
				/// Enum for determining which direction a player is facing.
				/// </summary>
				enum FACING {
					UP,
					DOWN,
					LEFT,
					RIGHT
				};

				/// <summary>
				/// The direction this player is currently facing.
				/// </summary>
				FACING facing = DOWN;

				/// <summary>
				/// The NavigableMap this player is abiding by.
				/// </summary>
				NavigableMap* navMap = nullptr;

				/// <summary>
				/// Whether or not this player is currently trying to move to a location they are unable of moving to.
				/// </summary>
				bool attemptingCollidingMove = false;

				void loop();
				/// <summary>
				/// Get the keys that are currently being pressed by the user that are relevant to player movement.
				/// </summary>
				/// <returns>Struct containing data on which keys are being pressed.</returns>
				currentlyPressingStruct getActiveKeys();

				/// <summary>
				/// Runs whenever the player changes tile.
				/// </summary>
				virtual void onChangeTile();

				/// <summary>
				/// The time of the last warp (world change).
				/// </summary>
				double lastWarp = 0;
				/// <summary>
				/// The time required to be waited before the player can warp (world change) again.
				/// </summary>
				double warpCooldown = 0.3;

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			private:
				/// <summary>
				/// The location the last move started in.
				/// </summary>
				vec3 moveStartPosition;
				/// <summary>
				/// The location of the player as of the last frame.
				/// </summary>
				vec3 lastLocation;
				/// <summary>
				/// The last direction the player was facing in.
				/// </summary>
				FACING lastFacing;
				/// <summary>
				/// Update the store of keys that are currently being pressed.
				/// </summary>
				void updateInputStatus();
			};
		}
	}
}

#endif