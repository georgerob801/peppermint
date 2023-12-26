#include <peppermint-preview/classes/game/components/WarpTile.h>

using namespace peppermint::game::components;

vector<byte> WarpTile::serialise() {
	vector<byte> out;

	unsigned int e = this->type;
	byte* toAdd = (byte*)reinterpret_cast<char*>(&e);

	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(toAdd[i]);
	}

	void* id = this;
	byte* toAdd2 = (byte*)reinterpret_cast<char*>(&id);

	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(toAdd2[i]);
	}

	byte* destWorldB = reinterpret_cast<byte*>(&this->destinationWorld);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(destWorldB[i]);
	}

	float floatsToAdd[] = {
		this->destinationCharacterPosition.x,
		this->destinationCharacterPosition.y,
		this->destinationCharacterPosition.z
	};

	for (unsigned int i = 0; i < 3; i++) {
		byte* floatB = reinterpret_cast<byte*>(&floatsToAdd[i]);
		for (unsigned int j = 0; j < sizeof(float); j++) {
			out.push_back(floatB[j]);
		}
	}

	byte* reqFacB = reinterpret_cast<byte*>(&this->requiresFacing);
	for (unsigned int i = 0; i < sizeof(bool); i++) {
		out.push_back(reqFacB[i]);
	}

	byte* facTGB = reinterpret_cast<byte*>((unsigned char*)&this->facingToGo);
	for (unsigned int i = 0; i < sizeof(unsigned char); i++) {
		out.push_back(facTGB[i]);
	}

	byte* facADB = reinterpret_cast<byte*>((unsigned char*)&this->facingAtDestination);
	for (unsigned int i = 0; i < sizeof(unsigned char); i++) {
		out.push_back(facADB[i]);
	}

	return out;
}

void WarpTile::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	this->destinationWorld = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	this->destinationCharacterPosition.x = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);
	this->destinationCharacterPosition.y = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);
	this->destinationCharacterPosition.z = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);

	
	this->requiresFacing = *reinterpret_cast<bool*>(&bytes[position]);
	position += sizeof(bool);
	this->facingToGo = (Facing)(*reinterpret_cast<unsigned char*>(&bytes[position]));
	position += sizeof(unsigned char);
	this->facingAtDestination = (Facing)(*reinterpret_cast<unsigned char*>(&bytes[position]));
	position += sizeof(unsigned char);


	this->deserialisedSize = sizeof(void*) + sizeof(unsigned int) + (3 * sizeof(float)) + sizeof(bool) + 2 * sizeof(unsigned char);
}