#include <peppermint-preview/classes/rendering/Tileset.h>

#include <peppermint-preview/Exceptions.hpp>
#include <format>

using namespace peppermint::rendering;

void Tileset::generateTextures() {
	for (unsigned int i = 0; i < this->textureSets.size(); i++) {
		this->textureSets[i]->generateAtlas();
	}
}

void Tileset::nextTextureSet() {
	this->currentTextureSet++;
	if (this->currentTextureSet >= this->textureSets.size()) {
		this->currentTextureSet = 0;
	}
}

TextureSet* Tileset::getCurrentTextureSet() {
	return this->textureSets[this->currentTextureSet];
}

void Tileset::goToTextureSet(int index) {
	if (index < 0 || index >= this->textureSets.size()) {
		throw peppermint::exceptions::rendering::tileset::InvalidTextureSetIndexException();
	}

	this->currentTextureSet = index;
}

void Tileset::generateDefaultTextureMappings() {
	for (unsigned int y = 0; y < this->getCurrentTextureSet()->atlas->getHeight(); y += this->tileSize.y) {
		for (unsigned int x = 0; x < this->getCurrentTextureSet()->atlas->getWidth(); x += this->tileSize.x) {
			this->textureMappings.push_back(Tileset::TileTextureMapping() = {
				.centre = vec2(x + (int)(this->tileSize.x / 2), y + (int)(this->tileSize.y / 2))
			});
		}
	}
	
}

vector<byte> Tileset::serialise() {
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

	unsigned int length = 0;
	byte* pathSizeB = reinterpret_cast<byte*>(&length);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(pathSizeB[i]);
	}

	vector<byte*> floatsToAdd;

	floatsToAdd.push_back(reinterpret_cast<byte*>(&this->tileSize.x));
	floatsToAdd.push_back(reinterpret_cast<byte*>(&this->tileSize.y));

	for (unsigned int i = 0; i < floatsToAdd.size(); i++) {
		for (unsigned int j = 0; j < sizeof(float); j++) {
			out.push_back(floatsToAdd[i][j]);
		}
	}

	unsigned int numTextureSets = this->textureSets.size();
	byte* numTextureSetsB = reinterpret_cast<byte*>(&numTextureSets);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(numTextureSetsB[i]);
	}

	for (unsigned int i = 0; i < this->textureSets.size(); i++) {
		byte* setIDB = reinterpret_cast<byte*>(&this->textureSets[i]);
		for (unsigned int j = 0; j < sizeof(void*); j++) {
			out.push_back(setIDB[j]);
		}
	}

	unsigned int numTextureMappings = this->textureMappings.size();
	byte* numTextureMappingsB = reinterpret_cast<byte*>(&numTextureMappings);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(numTextureMappingsB[i]);
	}

	for (unsigned int i = 0; i < this->textureMappings.size(); i++) {
		byte* x = reinterpret_cast<byte*>(&this->textureMappings[i].centre.x);
		for (unsigned int j = 0; j < sizeof(float); j++) {
			out.push_back(x[j]);
		}

		byte* y = reinterpret_cast<byte*>(&this->textureMappings[i].centre.y);
		for (unsigned int j = 0; j < sizeof(float); j++) {
			out.push_back(y[j]);
		}
	}

	//out += "Tileset:\n";
	//out += std::format("ID: {}\n", (void*)this);
	//out += "Data:\n";
	//out += std::format("TextureSets: {}\n", this->textureSets.size());

	//for (unsigned int i = 0; i < this->textureSets.size(); i++) {
	//	out += std::format("TextureSetID: {}\n", (void*)this->textureSets[i]);
	//}

	//out += std::format("TileSize.X: {}\n", this->tileSize.x);
	//out += std::format("TileSize.Y: {}\n", this->tileSize.y);

	//out += std::format("TextureMappings: {}\n", this->textureMappings.size());
	//
	//for (unsigned int i = 0; i < this->textureMappings.size(); i++) {
	//	out += std::format("TextureMapping{}:\n", i);
	//	out += std::format("TextureMapping.Centre.X: {}\n", this->textureMappings[i].centre.x);
	//	out += std::format("TextureMapping.Centre.Y: {}\n", this->textureMappings[i].centre.y);
	//}

	//out += std::format("CurrentTextureSet: {}\n", this->currentTextureSet);

	return out;
}

void Tileset::deserialise(vector<byte> bytes) {
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

	this->path = (char*)ePath.c_str();

	this->tileSize.x = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);
	this->tileSize.y = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);

	unsigned int numTextureSets = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	for (unsigned int i = 0; i < numTextureSets; i++) {
		this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
		position += sizeof(void*);
	}

	unsigned int numTextureMappings = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	for (unsigned int i = 0; i < numTextureMappings; i++) {
		float x = *reinterpret_cast<float*>(&bytes[position]);
		position += sizeof(float);
		float y = *reinterpret_cast<float*>(&bytes[position]);
		position += sizeof(float);
		this->textureMappings.push_back(TileTextureMapping() = {
			.centre = vec2(x, y)
		});
	}

	this->deserialisedSize = sizeof(void*) + sizeof(unsigned int) + (2 * sizeof(float)) + sizeof(unsigned int) + (numTextureSets * sizeof(void*)) + sizeof(unsigned int) + (numTextureMappings * (2 * sizeof(float)));
}