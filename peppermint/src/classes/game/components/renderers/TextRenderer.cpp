#include <peppermint/classes/game/components/renderers/TextRenderer.h>
#include <peppermint/managers/LogManager.h>

#include <glad/glad.h>

using namespace peppermint::game::components;
using namespace peppermint::rendering::text;

TextRenderer::TextRenderer() {
	this->type = TEXT_RENDERER;
	this->bufferType = GL_DYNAMIC_DRAW;
	this->meshType = Mesh::TEXT;
}

void TextRenderer::generateVertices() {
	this->vertices.clear();
	vector<Vertex>().swap(this->vertices);

	this->textures.clear();
	vector<Texture*>().swap(this->textures);

	// check if font has been changed
	if (this->fontFile != this->lastFontFile) {
		this->font = peppermint::rendering::text::FTManager::getFont(this->fontFile);

		if (this->font == nullptr) {
			peppermint::managers::LogManager::error(format("Could not find registered font from file '{}'", this->fontFile->path));
			return;
		}
	}

	float xOffset = 0.0f;
	float yOffset = 0.0f;

	for (unsigned int i = 0; i < this->text.length(); i++) {
		// loop over every character (ignoring null terminator)
		char toProcess = this->text.c_str()[i];

		Character* c = this->font->getCharacter(toProcess, this->pixelSize);

		float xPos = xOffset + c->bearing.x;
		float yPos = yOffset - (c->size.y - c->bearing.y);

		float w = c->size.x;
		float h = c->size.y;

		Vertex vs[4] = {
			Vertex {
				vec3(xPos, yPos, 0.0f),
				vec2(0.0f, 1.0f)
			},
			Vertex {
				vec3(xPos + w, yPos, 0.0f),
				vec2(1.0f, 1.0f)
			},
			Vertex {
				vec3(xPos, yPos + h, 0.0f),
				vec2(0.0f, 0.0f)
			},
			Vertex {
				vec3(xPos + w, yPos + h, 0.0f),
				vec2(1.0f, 0.0f)
			}
		};

		for (unsigned int j = 0; j < 4; j++) this->vertices.push_back(vs[j]);

		this->textures.push_back(c->tex);

		xOffset += (c->advance >> 6);

		// tell things to actually remesh this renderer
		this->requiresRemeshing = true;
	}

}