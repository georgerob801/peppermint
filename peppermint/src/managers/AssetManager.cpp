#include <peppermint/managers/AssetManager.h>

#include <format>

#include <iostream>
#include <fstream>

using namespace peppermint::managers;

unsigned int AssetManager::currentId = 0;

AssetManager::~AssetManager() {
	for (unsigned int i = 0; i < this->assets.size(); i++) {
		delete assets[i];
	}
}

peppermint::Asset* AssetManager::newAsset(peppermint::Asset::ASSET_TYPE type) {
	Asset* newAsset = new Asset(type);
	this->registerAsset(newAsset);
	return newAsset;
}

void AssetManager::registerAsset(Asset* asset) {
	asset->id = ++this->currentId;
	std::vector<Asset*>::iterator pos = std::find(this->assets.begin(), this->assets.end(), asset);
	if (pos == this->assets.end()) this->assets.push_back(asset);
}

void AssetManager::unregisterAsset(Asset* asset) {
	std::vector<Asset*>::iterator pos = std::find(this->assets.begin(), this->assets.end(), asset);
	if (pos != this->assets.end()) this->assets.erase(pos);

	asset->id = NULL;
}

void AssetManager::unregisterAsset(unsigned int id) {
	std::vector<Asset*>::iterator pos = std::find_if(this->assets.begin(), this->assets.end(), [id](const Asset* x) { return x->id == id; });
	if (pos != this->assets.end()) {
		(*pos)->id = NULL;
		this->assets.erase(pos);
	}

	
}



void AssetManager::saveAssetFile(const char* filename) {
	this->saveAssetFile((char*)filename);
}

void AssetManager::saveAssetFile(char* filename) {
	std::ofstream assetFile(filename, std::ios::out | std::ios::binary);

	vector<byte> serialised = this->serialise();

	if (serialised.size() > 0) assetFile.write(reinterpret_cast<const char*>(&serialised[0]), serialised.size());

	assetFile.close();
}



vector<byte> AssetManager::serialise() {
	vector<byte> out;

	out.push_back((byte)0x02);
	out.push_back((byte)0x00);

	while (out.size() < 16) out.push_back((byte)0x00);

	// number of assets
	unsigned int size = this->assets.size();
	byte* sizeBytes = reinterpret_cast<byte*>(&size);

	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(sizeBytes[i]);
	}



	//out += "AssetManager:\n";
	//out += std::format("Assets: {}\n", this->assets.size());

	//for (unsigned int i = 0; i < this->assets.size(); i++) {
	//	out += this->assets[i]->serialise();
	//}

	return out;
}

void AssetManager::deserialise(vector<byte> bytes) {

}