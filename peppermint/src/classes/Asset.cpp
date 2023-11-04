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

	//out += "Asset:\n";
	//out += std::format("ID: {}\n", this->id);
	//out += "Data:\n";
	//out += std::format("Type: {}\n", (unsigned int)this->type);
	//out += std::format("Path: {}\n", this->path);

	return out;
}

void Asset::deserialise(vector<byte> bytes) {

}