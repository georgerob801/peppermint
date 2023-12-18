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

void SoundSource::start() {
	if (this->playByDefault) {
		this->play();
	}
}

void SoundSource::loop() {
	if (((GameObject*)this->getGameObject())->transform->getGlobalPosition() != this->lastPosition) {
		// position
		vec3 curPos = ((GameObject*)this->getGameObject())->transform->getGlobalPosition();
		alSource3f(this->sourceIndex, AL_POSITION, curPos.x, curPos.y, curPos.z);
		if (this->useDoppler) {
			// velocity
			vec3 vel = (curPos - this->lastPosition) / (float)peppermint::managers::EngineManager::deltaTime;
			alSource3f(this->sourceIndex, AL_VELOCITY, vel.x, vel.y, vel.z);
		}
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

vector<byte> SoundSource::serialise() {
	vector<byte> out;

	unsigned int e = this->type;
	byte* toAdd = reinterpret_cast<byte*>(&e);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(toAdd[i]);
	}

	void* id = this;
	toAdd = reinterpret_cast<byte*>(&id);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->useDoppler);
	for (unsigned int i = 0; i < sizeof(bool); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->gain);
	for (unsigned int i = 0; i < sizeof(float); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->pitch);
	for (unsigned int i = 0; i < sizeof(float); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->loopSound);
	for (unsigned int i = 0; i < sizeof(bool); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->playByDefault);
	for (unsigned int i = 0; i < sizeof(bool); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->sound->asset);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(toAdd[i]);
	}

	return out;
}

void SoundSource::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	this->useDoppler = *reinterpret_cast<bool*>(&bytes[position]);
	position += sizeof(bool);

	this->setGain(*reinterpret_cast<float*>(&bytes[position]));
	position += sizeof(float);

	this->setPitch(*reinterpret_cast<float*>(&bytes[position]));
	position += sizeof(float);
	
	this->setLoop(*reinterpret_cast<bool*>(&bytes[position]));
	position += sizeof(bool);
	
	this->playByDefault = *reinterpret_cast<bool*>(&bytes[position]);
	position += sizeof(bool);

	this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
	position += sizeof(void*);

	this->deserialisedSize = position;
}