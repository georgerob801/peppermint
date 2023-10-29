#include <peppermint/classes/rendering/Tileset.h>

#include <peppermint/Exceptions.hpp>

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