#include <peppermint-preview/classes/sound/SoundDevice.h>

#include <format>
#include <peppermint-preview/Exceptions.hpp>
#include <peppermint-preview/managers/LogManager.h>

using namespace peppermint::sound;
using namespace peppermint::managers;

using namespace std;

SoundDevice::SoundDevice() {

}

SoundDevice::~SoundDevice() {
	this->closeDevice();
}

void SoundDevice::openDevice(const ALchar* deviceName) {
	const char* logName = deviceName != NULL ? deviceName : "DEFAULT";
	LogManager::debug(format("Attempting to open sound device {}", logName));
	this->device = alcOpenDevice(deviceName);

	if (!this->device) throw peppermint::exceptions::sound::device::NoDeviceAvailableException();
	LogManager::debug(format("Opened sound device {} successfully", logName));

	LogManager::debug(format("Attempting to create sound context for sound device {}", logName));
	this->context = alcCreateContext(this->device, NULL);
	
	if (!this->device) throw peppermint::exceptions::sound::device::CannotCreateContextException();
	LogManager::debug(format("Created sound context for {} successfully", logName));

	if (alcIsExtensionPresent(this->device, "ALC_ENUMERATE_ALL_TEXT")) this->name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
	if (this->name.length() == 0 || alcGetError(this->device) != ALC_NO_ERROR) this->name = alcGetString(this->device, ALC_DEVICE_SPECIFIER);
	LogManager::debug(format("Sound device {} has name '{}'", logName, this->name));

	LogManager::info(format("Opened sound device {}", this->name));
}

void SoundDevice::closeDevice() {
	LogManager::debug(format("Attempting to close audio device {}", this->name));
	LogManager::debug("Removing sound context");
	if (!alcMakeContextCurrent(NULL)) throw peppermint::exceptions::sound::device::CannotRemoveContextException();
	LogManager::debug("Removed sound context");
	LogManager::debug("Deleting sound context");
	alcDestroyContext(this->context);
	LogManager::debug("Deleted sound context");
	LogManager::debug("Closing device");
	if (!alcCloseDevice(this->device)) throw peppermint::exceptions::sound::device::CannotCloseDeviceException();
	LogManager::info(format("Successfully closed audio device {}", this->name));
}

std::string SoundDevice::getName() {
	return this->name;
}

void SoundDevice::use() {
	alcMakeContextCurrent(this->context);
}

void SoundDevice::usent() {
	if (!alcMakeContextCurrent(NULL)) throw peppermint::exceptions::sound::device::CannotRemoveContextException();
}