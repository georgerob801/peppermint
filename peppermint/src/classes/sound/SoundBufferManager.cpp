#include <peppermint-preview/classes/sound/SoundBufferManager.h>

#include <peppermint-preview/Exceptions.hpp>
#include <AL/alext.h>
#include <peppermint-preview/managers/LogManager.h>

using namespace peppermint::sound;
using namespace peppermint::managers;

SoundBufferManager::~SoundBufferManager() {
	LogManager::debug("Deleting all sound buffers");
	vector<ALuint> bufferIndices;
	bufferIndices.reserve(this->soundBuffers.size());
	for (unsigned int i = 0; i < this->soundBuffers.size(); i++) {
		bufferIndices.push_back(this->soundBuffers[i]->bufferIndex);
	}
	alDeleteBuffers(this->soundBuffers.size(), bufferIndices.data());
	LogManager::debug("Deleted all sound buffers");
	this->soundBuffers.clear();
}

Sound* SoundBufferManager::addSound(peppermint::Asset* asset) {
	LogManager::debug(format("Attempting to load sound from asset {} (path '{}')", (void*)asset, asset->path));
	Sound* sound = new Sound();
	sound->asset = asset;

	// get the file
	SNDFILE* soundFile = sf_open(asset->path, SFM_READ, &sound->sfInfo);

	// check it didn't die
	if (!soundFile) {
		delete sound;
		throw peppermint::exceptions::sound::file::CannotOpenFileException();
	}

	// check the sound is useable
	if (sound->sfInfo.frames < 1 || sound->sfInfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sound->sfInfo.channels) {
		delete sound;
		sf_close(soundFile);
		throw peppermint::exceptions::sound::file::BadSampleCountException();
	}
	
	// determine format
	sound->format = AL_NONE;
	switch (sound->sfInfo.channels) {
	case 1:
		sound->format = AL_FORMAT_MONO16;
		break;
	case 2:
		sound->format = AL_FORMAT_STEREO16;
		break;
	case 3:
		if (sf_command(soundFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) sound->format = AL_FORMAT_BFORMAT2D_16;
		break;
	case 4:
		if (sf_command(soundFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) sound->format = AL_FORMAT_BFORMAT3D_16;
	default:
		delete sound;
		sf_close(soundFile);
		throw peppermint::exceptions::sound::file::UnsupportedChannelCountException();
		break;
	}

	if (sound->format == AL_NONE) {
		delete sound;
		sf_close(soundFile);
		throw peppermint::exceptions::sound::file::UnsupportedChannelCountException();
	}

	// wooo decoding time
	short* soundMemoryBuffer = static_cast<short*>(malloc((size_t)(sound->sfInfo.frames * sound->sfInfo.channels) * sizeof(short)));

	sf_count_t numSamples = sf_readf_short(soundFile, soundMemoryBuffer, sound->sfInfo.frames);

	if (numSamples < 1) {
		free(soundMemoryBuffer);
		sf_close(soundFile);
		delete sound;
		throw peppermint::exceptions::sound::file::CouldNotReadSamplesException();
	}

	LogManager::debug(format("Loaded sound at from asset {} (path '{}') correctly", (void*)asset, asset->path));

	ALsizei numBytes = (ALsizei)(numSamples * sound->sfInfo.channels) * (ALsizei)sizeof(short);

	// put in an actual buffer object
	sound->bufferIndex = 0;
	alGenBuffers(1, &sound->bufferIndex);
	alBufferData(sound->bufferIndex, sound->format, soundMemoryBuffer, numBytes, sound->sfInfo.samplerate);

	free(soundMemoryBuffer);
	sf_close(soundFile);
	
	// die if required (errors)
	ALenum err = alGetError();
	if (err != AL_NO_ERROR) {
		if (sound->bufferIndex && alIsBuffer(sound->bufferIndex)) alDeleteBuffers(1, &sound->bufferIndex);
		delete sound;
		throw peppermint::exceptions::sound::openal::GenericException(alGetString(err));
	}

	this->soundBuffers.push_back(sound);

	return sound;
}

bool SoundBufferManager::removeSound(Sound* sound) {
	return this->removeSound(sound->bufferIndex);
}

bool SoundBufferManager::removeSound(const ALuint& bufferIndex) {
	LogManager::debug(format("Attempting to remove sound buffer with index {}", bufferIndex));
	vector<Sound*>::iterator item = find_if(this->soundBuffers.begin(), this->soundBuffers.end(), [bufferIndex](Sound* item) { return item->bufferIndex == bufferIndex; });
	if (item == this->soundBuffers.end()) {
		LogManager::debug(format("Sound buffer with index {} does not exist", bufferIndex));
		return false;
	}
	LogManager::debug(format("Found sound with buffer index {}, deleting", bufferIndex));
	alDeleteBuffers(1, &(*item)->bufferIndex);
	this->soundBuffers.erase(item);
	LogManager::debug(format("Deleted sound with buffer index {}", bufferIndex));
	return true;
}