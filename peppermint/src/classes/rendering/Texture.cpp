#include <peppermint/classes/rendering/Texture.h>

#include <stb_image/stb_image.h>
#include <glad/glad4.h>
#include <peppermint/Exceptions.hpp>

using namespace peppermint::rendering;


Texture::Texture() : Asset(AssetType::TEXTURE) {
	glGenTextures(1, &this->glTextureLocation);

	glActiveTexture(GL_TEXTURE0);
	this->bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	this->height = NULL;
	this->width = NULL;
	this->nrChannels = NULL;
}

Texture::Texture(Asset* asset) : Asset(AssetType::TEXTURE) {
	this->imageAsset = asset;

	glGenTextures(1, &this->glTextureLocation);

	glActiveTexture(GL_TEXTURE0);
	this->bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	this->loadFromAsset();
}

Texture::~Texture() {
	glDeleteTextures(1, &this->glTextureLocation);
}

void Texture::loadFromAsset() {
	char* path = this->imageAsset->path;
	unsigned char* data = stbi_load(path, &this->width, &this->height, &this->nrChannels, 0);

	glActiveTexture(GL_TEXTURE0);
	this->bind();
	if (data) {
		if (this->nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		} else if (this->nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		throw peppermint::exceptions::rendering::texture::CannotLoadTextureException();
	}

	stbi_image_free(data);
}

int Texture::getWidth() {
	return this->width;
}

int Texture::getHeight() {
	return this->height;
}

int Texture::getNrChannels() {
	return this->nrChannels;
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, this->glTextureLocation);
}

void Texture::setImageAsset(Asset* asset) {
	this->imageAsset = asset;
}

vector<byte> Texture::serialise() {
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

	byte* imageAssetID = reinterpret_cast<byte*>(&this->imageAsset);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(imageAssetID[i]);
	}

	//out += "Texture:\n";
	//out += std::format("ID: {}\n", (void*)this);
	//out += std::format("ImageAssetID: {}\n", this->imageAsset->id);

	return out;
}

void Texture::deserialise(vector<byte> bytes) {
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

	this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
	
	this->deserialisedSize = sizeof(void*) + sizeof(unsigned int) + (ePath.size() * sizeof(char)) + sizeof(void*);
}