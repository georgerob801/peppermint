#include <peppermint/classes/rendering/Tileset.h>

#include <peppermint/Exceptions.hpp>
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

}