#include <peppermint/managers/AssetManager.h>

#include <peppermint/Exceptions.hpp>

#include <peppermint/classes/rendering/Text.h>

#include <format>
#include <iostream>
#include <fstream>

#include <peppermint/classes/rendering/Texture.h>
#include <peppermint/classes/rendering/TextureSet.h>
#include <peppermint/classes/rendering/Tileset.h>
#include <peppermint/classes/game/TilesetAnimation.h>

#include <peppermint/managers/EngineManager.h>

using namespace peppermint::managers;
using namespace peppermint::rendering;

unsigned int AssetManager::currentId = 0;

AssetManager::~AssetManager() {
	for (unsigned int i = 0; i < this->assets.size(); i++) {
		delete assets[i];
	}

	this->assets.clear();
}

peppermint::Asset* AssetManager::newAsset(peppermint::Asset::AssetType type) {
	Asset* newAsset = new Asset(type);
	this->registerAsset(newAsset);
	return newAsset;
}

void AssetManager::registerAsset(Asset* asset) {
	std::vector<Asset*>::iterator pos = std::find(this->assets.begin(), this->assets.end(), asset);
	if (pos == this->assets.end()) this->assets.push_back(asset);
}

void AssetManager::unregisterAsset(Asset* asset) {
	std::vector<Asset*>::iterator pos = std::find(this->assets.begin(), this->assets.end(), asset);
	if (pos != this->assets.end()) this->assets.erase(pos);
}

void AssetManager::saveAssetFile() {
	std::ofstream assetFile(this->assetFileAsset->path, std::ios::out | std::ios::binary);

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

	for (unsigned int i = 0; i < this->assets.size(); i++) {
		vector<byte> serialisedAsset = this->assets[i]->serialise();
		out.insert(out.end(), serialisedAsset.begin(), serialisedAsset.end());
	}

	//out += "AssetManager:\n";
	//out += std::format("Assets: {}\n", this->assets.size());

	//for (unsigned int i = 0; i < this->assets.size(); i++) {
	//	out += this->assets[i]->serialise();
	//}

	return out;
}

void AssetManager::loadAssetFile(Asset* assetFileIn) {
	this->assetFileAsset = assetFileIn;
	std::ifstream assetFile(assetFileIn->path, std::ios::binary | std::ios::in);
	assetFile.unsetf(std::ios::skipws);

	std::streampos fileSize;

	assetFile.seekg(0, std::ios::end);
	fileSize = assetFile.tellg();
	assetFile.seekg(0, std::ios::beg);

	std::vector<unsigned char> chars;
	chars.reserve(fileSize);

	chars.insert(chars.begin(), std::istream_iterator<unsigned char>(assetFile), std::istream_iterator<unsigned char>());

	std::vector<byte> allBytes;
	allBytes.reserve(fileSize);
	for (unsigned int i = 0; i < chars.size(); i++) {
		allBytes.push_back((byte)chars[i]);
	}

	this->deserialise(allBytes);

	this->assets.push_back(assetFileIn);
}

void AssetManager::deserialise(vector<byte> bytes) {
	if (bytes.size() < 16) {
		throw peppermint::exceptions::serialisation::asset::CorruptedFileException();
	}
	
	if (bytes[0x00] != (byte)0x02) {
		throw peppermint::exceptions::serialisation::asset::InvalidFileTypeException();
	}

	// delete assets
	this->assets.clear();
	// free memory
	vector<Asset*>().swap(this->assets);

	unsigned long long position = 0x10;
	unsigned int numAssets = *reinterpret_cast<unsigned int*>(&bytes[position]);

	position += sizeof(unsigned int);

	for (unsigned int i = 0; i < numAssets; i++) {
		Asset::AssetType type = (Asset::AssetType)(*reinterpret_cast<unsigned int*>(&bytes[position]));
		position += sizeof(unsigned int);

		Asset* asset;
		vector<byte> subVector(bytes.size() - position);

		switch (type) {
		case Asset::IMAGE:
		case Asset::FRAGMENT_SHADER_SOURCE:
		case Asset::VERTEX_SHADER_SOURCE:
		case Asset::PPMINT_ASSET_FILE:
		case Asset::PPMINT_GAME_FILE:
		case Asset::PPMINT_WORLD_FILE:
			asset = new Asset(type);
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			asset->deserialise(subVector);
			break;
		case Asset::TEXTURE:
			asset = new Texture();
			copy(bytes.begin() + position, bytes.end(), subVector.begin());
			
			asset->deserialise(subVector);
			break;
		case Asset::TEXTURE_SET:
			asset = new TextureSet();
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			asset->deserialise(subVector);
			break;
		case Asset::TILESET:
			asset = new Tileset();
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			asset->deserialise(subVector);
			break;
		case Asset::TILESET_ANIMATION:
			asset = new peppermint::game::TilesetAnimation();
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			asset->deserialise(subVector);
			break;
		case Asset::SOUND:
			asset = new Asset(type);
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			asset->deserialise(subVector);

			EngineManager::soundManager->sbm->addSound(asset);
			break;
		case Asset::SHADER:
			asset = new Shader();
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			asset->deserialise(subVector);
			break;
		case Asset::FONT:
			asset = new Asset(type);
			copy(bytes.begin() + position, bytes.end(), subVector.begin());

			asset->deserialise(subVector);

			peppermint::rendering::text::FTManager::addFont(asset);

			break;
		default:
			throw peppermint::exceptions::serialisation::asset::CorruptedFileException();
		}

		this->assets.push_back(asset);
		position += asset->getDeserialisedSize();
	}

	// pass over assets to setup any links
	for (unsigned int i = 0; i < this->assets.size(); i++) {
		switch (this->assets[i]->type) {
		case Asset::TEXTURE: 
		{
			Texture* tex = (Texture*)this->assets[i];
			
			void* imageSerID = tex->relatedSerialisedIDs[0];
			vector<Asset*>::iterator index = find_if(this->assets.begin(), this->assets.end(), [imageSerID](Asset* item) { return item->serialisedID == imageSerID; });
			
			if (index == this->assets.end()) throw peppermint::exceptions::serialisation::asset::CorruptedFileException();

			tex->setImageAsset(*index);

			tex->loadFromAsset();
			break;
		}
		case Asset::TEXTURE_SET:
		{
			TextureSet* ts = (TextureSet*)this->assets[i];

			for (unsigned int j = 0; j < ts->relatedSerialisedIDs.size(); j++) {
				void* texSerID = ts->relatedSerialisedIDs[j];

				vector<Asset*>::iterator index = find_if(this->assets.begin(), this->assets.end(), [texSerID](Asset* item) { return item->serialisedID == texSerID; });

				if (index == this->assets.end()) throw peppermint::exceptions::serialisation::asset::CorruptedFileException();

				ts->addTexture((Texture*)(*index));
			}
			break;
		}
		case Asset::TILESET:
		{
			Tileset* tset = (Tileset*)this->assets[i];

			for (unsigned int j = 0; j < tset->relatedSerialisedIDs.size(); j++) {
				void* texSetID = tset->relatedSerialisedIDs[j];

				vector<Asset*>::iterator index = find_if(this->assets.begin(), this->assets.end(), [texSetID](Asset* item) { return item->serialisedID == texSetID; });

				if (index == this->assets.end()) throw peppermint::exceptions::serialisation::asset::CorruptedFileException();

				tset->textureSets.push_back((TextureSet*)(*index));
			}

			break;
		}
		case Asset::SHADER:
		{
			Shader* sh = (Shader*)this->assets[i];

			void* toFindVert = sh->relatedSerialisedIDs[0];
			void* toFindFrag = sh->relatedSerialisedIDs[1];

			Asset* vert;
			Asset* frag;

			vector<Asset*>::iterator index = find_if(this->assets.begin(), this->assets.end(), [toFindVert](Asset* item) { return item->serialisedID == toFindVert; });
			if (index == this->assets.end()) throw peppermint::exceptions::serialisation::asset::CorruptedFileException();
			vert = *index;
			index = find_if(this->assets.begin(), this->assets.end(), [toFindFrag](Asset* item) { return item->serialisedID == toFindFrag; });
			if (index == this->assets.end()) throw peppermint::exceptions::serialisation::asset::CorruptedFileException();
			frag = *index;

			sh->loadFromAssets(vert, frag);
			break;
		}
		default:
			break;
		}
	}
}