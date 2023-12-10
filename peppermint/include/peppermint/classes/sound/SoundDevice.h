#ifndef PPMINT_SOUND_DEVICE_H
#define PPMINT_SOUND_DEVICE_H

#include <AL/al.h>
#include <AL/alc.h>

#include <string>

namespace peppermint {
	namespace sound {
		class SoundDevice {
		public:
			/// <summary>
			/// Create a new SoundDevice.
			/// </summary>
			SoundDevice();
			/// <summary>
			/// Delete this SoundDevice.
			/// </summary>
			~SoundDevice();

			/// <summary>
			/// Open a specified sound device.
			/// </summary>
			/// <param name="deviceName">The name of the device to open. NULL reverts to the default device.</param>
			void openDevice(const ALchar* deviceName);
			/// <summary>
			/// Set this SoundDevice as the device to use.
			/// </summary>
			void use();
			/// <summary>
			/// Set this SoundDevice as not the device to use.
			/// </summary>
			void usent();

			/// <summary>
			/// Close the device this SoundDevice is connected to.
			/// </summary>
			void closeDevice();
			/// <summary>
			/// Get this SoundDevice's name.
			/// </summary>
			/// <returns>This SoundDevice's name.</returns>
			std::string getName();
		private:
			ALCcontext* context = nullptr;
			ALCdevice* device = nullptr;

			std::string name;
		};
	}
}

#endif