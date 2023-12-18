#ifndef PPMINT_COMPONENT_SOUND_LISTENER_H
#define PPMINT_COMPONENT_SOUND_LISTENER_H

#include <peppermint/classes/game/Component.h>

#include <glm/glm.hpp>

#include <peppermint/classes/game/components/Camera.h>
#include <peppermint/classes/sound/ALErrorCheck.hpp>

using namespace glm;

namespace peppermint {
	namespace game {
		namespace components {
			class SoundListener : public Component, public peppermint::sound::ALErrorCheck {
			public:
				SoundListener();

				Camera* facingCamera = nullptr;

				void loop();

				void setGain(float gain);

				bool useDoppler = false;

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			private:
				vec3 lastPosition = vec3(0.0f, 0.0f, 0.0f);

				float gain = 1.0f;
			};
		}
	}
}

#endif