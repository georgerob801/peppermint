#include <peppermint/classes/rendering/Texture.h>

#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <peppermint/Exceptions.hpp>

using namespace peppermint::rendering;


Texture::Texture() : Asset(ASSET_TYPE::TEXTURE) {
	glGenTextures(1, &this->glTextureLocation);

	this->height = NULL;
	this->width = NULL;
	this->nrChannels = NULL;
}

Texture::Texture(Asset* asset) : Asset(ASSET_TYPE::TEXTURE) {
	this->imageAsset = asset;
	char* path = asset->path;
	unsigned char* data = stbi_load(path, &this->width, &this->height, &this->nrChannels, 0);

	glGenTextures(1, &this->glTextureLocation);
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

#include <format>

vector<byte> Texture::serialise() {
	vector<byte> out;

	//out += "Texture:\n";
	//out += std::format("ID: {}\n", (void*)this);
	//out += std::format("ImageAssetID: {}\n", this->imageAsset->id);

	return out;
}

void Texture::deserialise(vector<byte> bytes) {

}