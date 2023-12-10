#include <peppermint/classes/game/components/renderers/SpriteRenderer.h>

using namespace peppermint::game::components;

SpriteRenderer::SpriteRenderer() {
	this->type = Component::SPRITE_RENDERER;
	this->textureSet = nullptr;
}

void SpriteRenderer::generateTextures() {
	this->textureSet->generateAtlas();
}

void SpriteRenderer::generateVertices() {
	this->vertices.clear();
	vector<Vertex>().swap(this->vertices);

	// once again should be testing only
	this->textures.push_back(this->textureSet->atlas);

	vector<Vertex> square = Mesh::SQUARE();

	float ratio = this->size.x / this->size.y;

	for (unsigned int i = 0; i < 4; i++) {
		vec3* posP = &square[i].position;
		if (ratio < 1.0f) posP->y *= ratio;
		else posP->x *= ratio;

		vec2* uvP = &square[i].uv;
		// make uv go in right place
		switch (i) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}

		uvP->x *= ((this->position.x / this->textureSet->atlas->getWidth()) + ((this->size.x / this->textureSet->atlas->getWidth()) / 2.0f));
		uvP->y *= ((this->position.y / this->textureSet->atlas->getHeight()) + ((this->size.y / this->textureSet->atlas->getHeight()) / 2.0f));

		this->vertices.push_back(square[i]);
	}
}

vector<byte> SpriteRenderer::serialise() {
	vector<byte> out;

	unsigned int e = this->type;
	byte* toAdd = reinterpret_cast<byte*>(&e);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(toAdd[i]);
	}

	void* id = this;
	byte* toAdd2 = reinterpret_cast<byte*>(&id);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(toAdd2[i]);
	}

	byte* textureSetIDB = reinterpret_cast<byte*>(&this->textureSet);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(textureSetIDB[i]);
	}

	vector<float> floatsToAdd;
	floatsToAdd.push_back(this->position.x);
	floatsToAdd.push_back(this->position.y);
	floatsToAdd.push_back(this->size.x);
	floatsToAdd.push_back(this->size.y);

	for (unsigned int i = 0; i < floatsToAdd.size(); i++) {
		byte* floatB = reinterpret_cast<byte*>(&floatsToAdd[i]);
		for (unsigned int j = 0; j < sizeof(float); j++) {
			out.push_back(floatB[j]);
		}
	}

	return out;
}

void SpriteRenderer::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
	position += sizeof(void*);

	this->position.x = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);
	this->position.y = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);
	this->size.x = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);
	this->size.y = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);

	this->deserialisedSize = position;
}