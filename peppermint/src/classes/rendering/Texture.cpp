#include <peppermint/classes/rendering/Texture.h>

#include <stb_image/stb_image.h>
#include <glad/glad.h>

using namespace peppermint::rendering;

Texture::Texture() {
	glGenTextures(1, &this->glTextureLocation);

	this->height = NULL;
	this->width = NULL;
	this->nrChannels = NULL;
	this->data = NULL;
}

Texture::Texture(char* path) {
	this->data = stbi_load(path, &this->width, &this->height, &this->nrChannels, 0);

	glGenTextures(1, &this->glTextureLocation);
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