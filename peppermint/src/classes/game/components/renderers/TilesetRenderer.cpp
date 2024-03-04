#include <peppermint/classes/game/components/renderers/TilesetRenderer.h>

#include <peppermint/managers/LogManager.h>

using namespace peppermint::managers;

using namespace peppermint::game::components;

TilesetRenderer::TilesetRenderer(unsigned int width, unsigned int height) {
	this->tileTypes = new unsigned short[width * height] { 0 };
	this->width = width;
	this->height = height;
	this->type = Component::TILESET_RENDERER;
}

TilesetRenderer::~TilesetRenderer() {
	delete[] this->tileTypes;
}

void TilesetRenderer::generateTextures() {
	this->tileset->generateTextures();
}

void TilesetRenderer::setTileAt(unsigned int x, unsigned int y, unsigned short value) {
	this->tileTypes[y * this->width + x] = value;
}

void TilesetRenderer::generateVertices() {
	this->vertices.clear();
	vector<Vertex>().swap(this->vertices);

	for (unsigned int i = 0; i < this->tileset->textureSets.size(); i++) {
		this->tileset->textureSets[i]->generateAtlas();
		this->textures.push_back(this->tileset->textureSets[i]->atlas);
	}

	vec2 scale = vec2(1.0f / (float)this->tileset->getCurrentTextureSet()->atlas->getWidth(), 1.0f / (float)this->tileset->getCurrentTextureSet()->atlas->getHeight());

	for (unsigned int y = 0; y < this->height; y++) {
		for (unsigned int x = 0; x < this->width; x++) {
			vector<Vertex> square = Mesh::SQUARE(vec3(x, y, 0.0f));
			for (unsigned char i = 0; i < 4; i++) {
				Tileset::TileTextureMapping mapping = this->tileset->textureMappings[this->tileTypes[(this->width * y) + x]];
				switch (i) {
				case 0:
					square[i].uv = (mapping.centre * scale) + (vec2(-(this->tileset->tileSize.x / 2), -(this->tileset->tileSize.y / 2)) * scale * 0.99f);
					break;
				case 1:
					square[i].uv = (mapping.centre * scale) + (vec2((this->tileset->tileSize.x / 2), -(this->tileset->tileSize.y / 2)) * scale * 0.99f);
					break;
				case 2:
					square[i].uv = (mapping.centre * scale) + (vec2(-(this->tileset->tileSize.x / 2), (this->tileset->tileSize.y / 2)) * scale * 0.99f);
					break;
				case 3:
					square[i].uv = (mapping.centre * scale) + (vec2((this->tileset->tileSize.x / 2), (this->tileset->tileSize.y / 2)) * scale * 0.99f);
					break;
				}
				this->vertices.push_back(square[i]);
			}
		}
	}
}

void TilesetRenderer::awake() {
	if (this->requiresRemesh) {
		this->generateVertices();
		this->requiresRemesh = false;
	}
}

void TilesetRenderer::fill(unsigned short value) {
	for (unsigned int i = 0; i < this->width * this->height; i++) {
		this->tileTypes[i] = value;
	}
}

vector<byte> TilesetRenderer::serialise() {
	vector<byte> out;

	unsigned int e = this->type;
	byte* toAdd = (byte*)reinterpret_cast<char*>(&e);

	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(toAdd[i]);
	}

	void* id = this;
	byte* toAdd2 = (byte*)reinterpret_cast<char*>(&id);

	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(toAdd2[i]);
	}

	byte* tilesetIDB = reinterpret_cast<byte*>(&this->tileset);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(tilesetIDB[i]);
	}

	vector<byte*> uintsToAdd;

	uintsToAdd.push_back(reinterpret_cast<byte*>(&this->width));
	uintsToAdd.push_back(reinterpret_cast<byte*>(&this->height));

	vector<byte*> shortsToAdd;

	for (unsigned int i = 0; i < this->width * this->height; i++) {
		shortsToAdd.push_back(reinterpret_cast<byte*>(&this->tileTypes[i]));
	}

	for (unsigned int i = 0; i < uintsToAdd.size(); i++) {
		for (unsigned int j = 0; j < sizeof(unsigned int); j++) {
			out.push_back(uintsToAdd[i][j]);
		}
	}

	for (unsigned int i = 0; i < shortsToAdd.size(); i++) {
		for (unsigned int j = 0; j < sizeof(unsigned short); j++) {
			out.push_back(shortsToAdd[i][j]);
		}
	}

	return out;
}

void TilesetRenderer::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
	position += sizeof(void*);

	position += 2 * sizeof(unsigned int);

	for (unsigned int i = 0; i < this->width * this->height; i++) {
		this->tileTypes[i] = *reinterpret_cast<unsigned short*>(&bytes[position]);
		position += sizeof(unsigned short);
	}

	this->deserialisedSize = (2 * sizeof(void*)) + (2 * sizeof(unsigned int)) + ((this->width * this->height) * sizeof(unsigned short));
}