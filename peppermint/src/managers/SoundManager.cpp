#include <peppermint-preview/managers/SoundManager.h>

using namespace peppermint::managers;

SoundManager::~SoundManager() {
	delete this->sbm;
	for (unsigned int i = 0; i < this->soundDevices.size(); i++) {
		this->soundDevices[i]->closeDevice();
	}
}

void SoundManager::initialiseWithDefaults() {
	SoundDevice* snd = new SoundDevice();
	snd->openDevice(NULL);
	snd->use();

	this->soundDevices.push_back(snd);

	this->sbm = new SoundBufferManager();
}