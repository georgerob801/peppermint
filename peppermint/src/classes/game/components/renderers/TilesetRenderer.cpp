#include <peppermint/classes/game/components/renderers/TilesetRenderer.h>

#include <peppermint/managers/LogManager.h>
using namespace peppermint::managers;

using namespace peppermint::game::components;

TilesetRenderer::TilesetRenderer(unsigned int width, unsigned int height) {
	this->tileTypes = new unsigned int[width * height] { 0 };
	this->width = width;
	this->height = height;
}

TilesetRenderer::~TilesetRenderer() {
	delete[] this->tileTypes;
}

void TilesetRenderer::generateVertices() {
	this->vertices.clear();

	for (unsigned int y = 0; y < this->height; y++) {
		for (unsigned int x = 0; x < this->width; x++) {
			vector<Vertex> square = Mesh::SQUARE(vec3(x + 1, y, 0.0f));
			for (unsigned char i = 0; i < 4; i++) {
				TileTextureMapping mapping = this->textureMappings[this->tileTypes[(this->width * y) + x]];
				switch (i) {
				case 0:
					square[i].uv = mapping.centre + vec2(-(this->tileset->tileSize / 2), -(this->tileset->tileSize / 2));
					break;
				case 1:
					square[i].uv = mapping.centre + vec2((this->tileset->tileSize / 2), -(this->tileset->tileSize / 2));
					break;
				case 2:
					square[i].uv = mapping.centre + vec2(-(this->tileset->tileSize / 2), (this->tileset->tileSize / 2));
					break;
				case 3:
					square[i].uv = mapping.centre + vec2((this->tileset->tileSize / 2), (this->tileset->tileSize / 2));
					break;
				}
				this->vertices.push_back(square[i]);
			}
		}
	}

	LogManager::warn(format("Size: {}", this->vertices.size()));
	LogManager::warn(format("Starts at {} {} {}", this->vertices[0].position.x, this->vertices[0].position.y, this->vertices[0].position.z));
	LogManager::warn(format("Starts at {} {} {}", this->vertices[1].position.x, this->vertices[1].position.y, this->vertices[1].position.z));
}

void TilesetRenderer::awake() {
	if (this->requiresRemesh) {
		this->generateVertices();
		this->requiresRemesh = false;
	}
}