#ifndef PPMINT_COMPONENT_SOUND_SOURCE_H
#define PPMINT_COMPONENT_SOUND_SOURCE_H

#include <peppermint/classes/game/Component.h>

#include <peppermint/classes/sound/ALErrorCheck.hpp>
#include <peppermint/classes/sound/SoundBufferManager.h>

#include <glm/glm.hpp>


using namespace peppermint::sound;

using namespace glm;

namespace peppermint {
	namespace game {
		namespace components {
			class SoundSource : public Component, public ALErrorCheck {
			public:
				SoundSource();
				~SoundSource();

				/// <summary>
				/// A pointer to the sound to play.
				/// </summary>
				Sound* sound = nullptr;

				/// <summary>
				/// Play this source's sound.
				/// </summary>
				void play();
				/// <summary>
				/// Pause this source's sound.
				/// </summary>
				void pause();
				/// <summary>
				/// Stop this source's sound.
				/// </summary>
				void stop();

				void loop();

				/// <summary>
				/// Set this source's pitch.
				/// </summary>
				/// <param name="pitch">Float to multiply the playback speed by.</param>
				void setPitch(float pitch);
				/// <summary>
				/// Set this source's gain.
				/// </summary>
				/// <param name="gain">Value to set the gain to.</param>
				void setGain(float gain);
				/// <summary>
				/// Set this source to be looping or not.
				/// </summary>
				/// <param name="loop">True/false depenidng on whether this source should loop or not.</param>
				void setLoop(bool loop);

				/// <summary>
				/// Get this source's current state.
				/// </summary>
				/// <returns>An ALenum of the source's current state.</returns>
				ALenum getSourceState();
			private:
				ALuint sourceIndex;
				ALuint lastBuffer = 0;

				float pitch = 1.0f;
				float gain = 1.0f;

				bool loopSound = false;

				vec3 lastPosition = vec3(0, 0, 0);
			};
		}
	}
}

#endif