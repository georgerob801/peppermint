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

	unsigned int numTextures = this->textures.size();
	byte* numTexturesB = reinterpret_cast<byte*>(&numTextures);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(numTexturesB[i]);
	}

	for (unsigned int i = 0; i < this->textures.size(); i++) {
		byte* textureIDB = reinterpret_cast<byte*>(&this->textures[i]);
		for (unsigned int j = 0; j < sizeof(void*); j++) {
			out.push_back(textureIDB[j]);
		}
	}

	//out += "TextureSet:\n";
	//out += std::format("ID: {}\n", (void*)this);
	//out += "Textures:\n";

	//for (unsigned int i = 0; i < this->textures.size(); i++) {
	//	out += std::format("TextureID: {}\n", (void*)this->textures[i]);
	//}

	return out;
}

void TextureSet::deserialise(vector<byte> bytes) {
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

	unsigned int numTextures = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	for (unsigned int i = 0; i < numTextures; i++) {
		this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
		position += sizeof(void*);
	}

	this->deserialisedSize = sizeof(void*) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(void*);
}