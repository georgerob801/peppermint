#ifndef PPMINT_COMPONENT_PLAYER_CONTROLLER_H
#define PPMINT_COMPONENT_PLAYER_CONTROLLER_H

#include <peppermint/classes/game/Component.h>
#include <peppermint/classes/game/components/NavigableMap.hpp>

#include <glm/glm.hpp>

using namespace glm;

struct currentlyPressingStruct {
	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;
};

struct currentlyMovingStruct {
	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;
};

namespace peppermint {
	namespace game {
		namespace components {
			class PlayerController : public Component {
			public:
				PlayerController() {
					this->type = Component::PLAYER_CONTROLLER;
				}

				float speed = 5.0f;
				float snapRange = 0.001f;

				currentlyPressingStruct currentlyPressing;
				currentlyMovingStruct currentlyMoving;

				enum FACING {
					UP,
					DOWN,
					LEFT,
					RIGHT
				};

				FACING facing = DOWN;

				NavigableMap* navMap = nullptr;

				bool attemptingCollidingMove = false;

				void loop();
				currentlyPressingStruct getActiveKeys();

				virtual void onChangeTile();

				double lastWarp = 0;
				double warpCooldown = 0.3;

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			private:
				vec3 moveStartPosition;
				vec3 lastLocation;
				FACING lastFacing;
				void updateInputStatus();
			};
		}
	}
}

#endif