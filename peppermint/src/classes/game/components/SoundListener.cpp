#include <peppermint/classes/game/components/SoundListener.h>

#include <peppermint/classes/game/GameObject.h>
#include <peppermint/managers/EngineManager.h>
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
		vec3 vel = (curPos - this->lastPosition) / (float)peppermint::managers::EngineManager::deltaTime;
		alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z);
		this->lastPosition = curPos;
	} else {
		alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	}
}