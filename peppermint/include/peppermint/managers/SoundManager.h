#ifndef PPMINT_SOUND_MANAGER_H
#define PPMINT_SOUND_MANAGER_H

#include <vector>
#include <peppermint/classes/sound/SoundDevice.h>
#include <peppermint/classes/sound/SoundBufferManager.h>

using namespace std;
using namespace peppermint::sound;

namespace peppermint {
	namespace managers {
		class SoundManager {
		public:
			/// <summary>
			/// Destroy this SoundManager.
			/// </summary>
			~SoundManager();

			/// <summary>
			/// Vector containing pointers to all SoundDevices.
			/// </summary>
			vector<SoundDevice*> soundDevices;
			/// <summary>
			/// A pointer to the SoundBufferManager to use.
			/// </summary>
			SoundBufferManager* sbm;

			/// <summary>
			/// Initialise this SoundManager using default devices.
			/// </summary>
			void initialiseWithDefaults();
		};
	}
}

#endif