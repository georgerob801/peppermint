#include <peppermint/classes/Asset.h>

#include <format>

using namespace peppermint;

Asset::Asset(ASSET_TYPE type) {
	this->type = type;
	this->path = nullptr;
}

void Asset::setPath(const char* path) {
	this->setPath((char*)path);
}

void Asset::setPath(char* path) {
	this->path = path;
}

vector<byte> Asset::serialise() {
	vector<byte> out;

	unsigned int typeCast = (unsigned int)this->type;
	byte* typeB = reinterpret_cast<byte*>(&typeCast);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(typeB[i]);
	}

	void* id = this;
	byte* idB = reinterpret_cast<byte*>(&id);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(idB[i]);
	}

	if (this->path != nullptr) {
		std::string pathStr(this->path);

		unsigned int length = pathStr.size();
		byte* pathSizeB = reinterpret_cast<byte*>(&length);
		for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
			out.push_back(pathSizeB[i]);
		}

		byte* pathB = reinterpret_cast<byte*>(this->path);
		for (unsigned int i = 0; i < length * sizeof(char); i++) {
			out.push_back(pathB[i]);
		}
	} else {
		unsigned int length = 0;
		byte* pathSizeB = reinterpret_cast<byte*>(&length);
		for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
			out.push_back(pathSizeB[i]);
		}
	}

	//out += "Asset:\n";
	//out += std::format("ID: {}\n", this->id);
	//out += "Data:\n";
	//out += std::format("Type: {}\n", (unsigned int)this->type);
	//out += std::format("Path: {}\n", this->path);

	return out;
}

#include <iostream>

void Asset::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	unsigned int pathLength = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	std::string ePath = "";

	for (unsigned int i = 0; i < pathLength; i++) {
		ePath += *reinterpret_cast<char*>(&bytes[position]);
		position += sizeof(char);
	}

	this->path = new char[ePath.size() + 1];

	strcpy_s(this->path, ePath.size() + 1, ePath.c_str());

	this->deserialisedSize = sizeof(void*) + sizeof(unsigned int) + (ePath.size() * sizeof(char));
}