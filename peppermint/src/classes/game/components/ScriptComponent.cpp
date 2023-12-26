#include <peppermint-preview/classes/game/components/ScriptComponent.h>

using namespace peppermint::game::components;

ScriptComponent::ScriptComponent() {
	this->type = SCRIPT_COMPONENT;
}

vector<byte> ScriptComponent::serialise() {
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

	unsigned int localType = this->getScriptType();
	toAdd = reinterpret_cast<byte*>(&localType);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(toAdd[i]);
	}

	vector<byte> data = this->serialiseData();

	unsigned long long dataSize = data.size();
	toAdd = reinterpret_cast<byte*>(&dataSize);
	for (unsigned int i = 0; i < sizeof(unsigned long long); i++) {
		out.push_back(toAdd[i]);
	}

	out.insert(out.end(), data.begin(), data.end());

	return out;
}

void ScriptComponent::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	// skip over script type as that should already be determined by world manager and script types
	position += sizeof(unsigned int);

	// send the remaining bytes over to deserialiseData
	unsigned long long numBytes = *reinterpret_cast<unsigned long long*>(&bytes[position]);
	position += sizeof(unsigned long long);

	vector<byte> subVector(bytes.begin() + position, bytes.begin() + position + numBytes);

	this->deserialiseData(subVector);
}

unsigned int ScriptComponent::getScriptType(vector<byte> bytes) {
	return *reinterpret_cast<unsigned int*>(&bytes[sizeof(void*)]);
}