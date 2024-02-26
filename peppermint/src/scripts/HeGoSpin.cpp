#include <peppermint/scripts/HeGoSpin.h>

#include <peppermint/managers/LogManager.h>
#include <peppermint/managers/EngineManager.h>

#include <peppermint/Exceptions.hpp>

using namespace peppermint::game::components;
using namespace peppermint::managers;

void HeGoSpin::start() {
	LogManager::info("Hello there!");
	LogManager::info("Check out the scripts folder to see how this code is being run.");
	LogManager::warn("ooh now it's orange");

	this->toothless = EngineManager::getWM()->getFirstComponent<Transform>();
}

void HeGoSpin::loop() {
	this->toothless->rotation.z = glm::two_pi<float>() * glm::sin(glfwGetTime());
}

vector<byte> HeGoSpin::serialiseData() {
	vector<byte> out;

	byte* vBytes = reinterpret_cast<byte*>(&this->toothless);
	for (unsigned int i = 0; i < sizeof(void*); i++) out.push_back(vBytes[i]);

	return out;
}

void HeGoSpin::deserialiseData(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
	position += sizeof(void*);

	this->deserialisedDataSize = position;
}

void HeGoSpin::makeConnections(vector<Asset*>* assets, vector<Component*>* components) {
	void* toFind = this->relatedSerialisedIDs[0];
	vector<Component*>::iterator it = find_if(components->begin(), components->end(), [toFind](Component* item) { return item->serialisedID == toFind; });

	if (it == components->end()) throw peppermint::exceptions::serialisation::world::CorruptedFileException();

	this->toothless = (Transform*)*it;
}