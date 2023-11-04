#include <peppermint/classes/rendering/TextureSet.h>

#include <format>

using namespace peppermint::rendering;

// TODO: write this function
void TextureSet::generateAtlas() {
	if (this->requiresAtlasGeneration) {
		this->atlas = this->textures[0];
		this->requiresAtlasGeneration = false;
	}
}

void TextureSet::addTexture(Texture* tex) {
	this->textures.push_back(tex);
}

vector<byte> TextureSet::serialise() {
	vector<byte> out;

	//out += "TextureSet:\n";
	//out += std::format("ID: {}\n", (void*)this);
	//out += "Textures:\n";

	//for (unsigned int i = 0; i < this->textures.size(); i++) {
	//	out += std::format("TextureID: {}\n", (void*)this->textures[i]);
	//}

	return out;
}

void TextureSet::deserialise(vector<byte> bytes) {

}