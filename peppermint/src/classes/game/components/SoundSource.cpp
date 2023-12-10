#include <peppermint/classes/game/components/SoundSource.h>

#include <peppermint/classes/game/GameObject.h>
#include <peppermint/managers/EngineManager.h>
#include <peppermint/Exceptions.hpp>

using namespace peppermint::game::components;

SoundSource::SoundSource() {
	this->type = Component::SOUND_SOURCE;
	alGenSources(1, &this->sourceIndex);
}

SoundSource::~SoundSource() {
	this->stop();

	alDeleteSources(1, &this->sourceIndex);
}

void SoundSource::loop() {
	if (((GameObject*)this->getGameObject())->transform->getGlobalPosition() != this->lastPosition) {
		// position
		vec3 curPos = ((GameObject*)this->getGameObject())->transform->getGlobalPosition();
		alSource3f(this->sourceIndex, AL_POSITION, curPos.x, curPos.y, curPos.z);
		// velocity
		vec3 vel = (curPos - this->lastPosition) / (float)peppermint::managers::EngineManager::deltaTime;
		alSource3f(this->sourceIndex, AL_VELOCITY, vel.x, vel.y, vel.z);
		this->lastPosition = ((GameObject*)this->getGameObject())->transform->getGlobalPosition();
	} else {
		// reset velocity if no movement
		alSource3f(this->sourceIndex, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	}
}

ALenum SoundSource::getSourceState() {
	ALenum val;
	alGetSourcei(this->sourceIndex, AL_SOURCE_STATE, &val);
	return val;
}

void SoundSource::setPitch(float pitch) {
	this->pitch = pitch;
	alSourcef(this->sourceIndex, AL_PITCH, this->pitch);

	this->errorCheck();
}

void SoundSource::setGain(float gain) {
	this->gain = gain;
	alSourcef(this->sourceIndex, AL_GAIN, this->gain);
}

void SoundSource::setLoop(bool loop) {
	this->loopSound = loop;
	alSourcei(this->sourceIndex, AL_LOOPING, this->loopSound);
}

void SoundSource::play() {
	this->stop();

	if (this->sound->bufferIndex != this->lastBuffer) {
		this->lastBuffer = this->sound->bufferIndex;
		alSourcei(this->sourceIndex, AL_BUFFER, (ALint)this->lastBuffer);
	}

	alSourcePlay(this->sourceIndex);

	this->errorCheck();
}

void SoundSource::pause() {
	if (this->getSourceState() == AL_PLAYING) {
		alSourcePause(this->sourceIndex);
	}

	this->errorCheck();
}

void SoundSource::stop() {
	if (this->getSourceState() == AL_PLAYING) {
		alSourceStop(this->sourceIndex);
	}

	this->errorCheck();
}