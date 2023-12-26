#ifndef PPMINT_SOUND_BUFFER_H
#define PPMINT_SOUND_BUFFER_H

#include <AL/al.h>
#include <vector>
#include <sndfile.h>

#include <peppermint-preview/classes/Asset.h>

namespace peppermint {
	namespace sound {
		/// <summary>
		/// Struct for tracking sound information.
		/// </summary>
		class Sound {
		public:
			/// <summary>
			/// The index of the buffer this sound is stored in.
			/// </summary>
			ALuint bufferIndex = NULL;
			/// <summary>
			/// The format this sound is stored in.
			/// </summary>
			ALenum format = AL_NONE;
			/// <summary>
			/// Information relating to the file this sound came from.
			/// </summary>
			SF_INFO sfInfo;
			/// <summary>
			/// A pointer to the asset that stores this sound's path.
			/// </summary>
			Asset* asset = nullptr;
		};

		class SoundBufferManager {
		public:
			/// <summary>
			/// Delete this SoundBufferManager.
			/// </summary>
			~SoundBufferManager();

			/// <summary>
			/// Add a sound to this SoundBufferManager.
			/// </summary>
			/// <param name="asset">A pointer to the asset containing this sound's path.</param>
			/// <returns>A pointer to the created sound.</returns>
			Sound* addSound(peppermint::Asset* asset);
			/// <summary>
			/// Remove a sound from this SoundBufferManager based on its buffer's index.
			/// </summary>
			/// <param name="bufferIndex">The index of the buffer to remove.</param>
			/// <returns>True/false depending on whether the sound was removed.</returns>
			bool removeSound(const ALuint& bufferIndex);
			/// <summary>
			/// Remove a sound from this SoundBufferManager.
			/// </summary>
			/// <param name="sound">A pointer to the sound to remove.</param>
			/// <returns>True/false depending on whether the sound was removed.</returns>
			bool removeSound(Sound* sound);
			/// <summary>
			/// Vector containing all sounds currently available for use.
			/// </summary>
			vector<Sound*> soundBuffers;
		};
	}
}

#endif