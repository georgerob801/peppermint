#include <peppermint-preview/classes/game/components/SoundListener.h>

#include <peppermint-preview/classes/game/GameObject.h>
#include <peppermint-preview/managers/EngineManager.h>
#include <AL/al.h>

using namespace peppermint::game::components;

SoundListener::SoundListener() {
	this->type = Component::SOUND_LISTENER;
}

void SoundListener::setGain(float gain) {
	this->gain = gain;
	alListenerf(AL_GAIN, this->gain);

	this->errorCheck();
}

void SoundListener::loop() {
	if (((GameObject*)this->getGameObject())->transform->getGlobalPosition() != this->lastPosition) {
		vec3 curPos = ((GameObject*)this->getGameObject())->transform->getGlobalPosition();
		alListener3f(AL_POSITION, curPos.x, curPos.y, curPos.z);
		if (this->useDoppler) {
			vec3 vel = (curPos - this->lastPosition) / (float)peppermint::managers::EngineManager::deltaTime;
			alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z);
		}
		this->lastPosition = curPos;
	} else {
		alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	}
}

vector<byte> SoundListener::serialise() {
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

	return out;
}

void SoundListener::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	this->useDoppler = *reinterpret_cast<bool*>(&bytes[position]);
	position += sizeof(bool);

	this->gain = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);

	this->deserialisedSize = position;
}