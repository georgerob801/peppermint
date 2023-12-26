#include <peppermint-preview/classes/game/components/renderers/TextRenderer.h>
#include <peppermint-preview/managers/LogManager.h>

#include <glad/glad.h>

using namespace peppermint::game::components;
using namespace peppermint::rendering::text;

TextRenderer::TextRenderer() {
	this->type = TEXT_RENDERER;
	this->bufferType = GL_DYNAMIC_DRAW;
	this->meshType = Mesh::TEXT;
}

string TextRenderer::getText() {
	return this->text;
}

void TextRenderer::setText(string text) {
	this->text = text;

	this->generateVertices();
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

	float relScale = 1.0f / this->pixelSize;

	for (unsigned int i = 0; i < this->text.length(); i++) {
		// loop over every character (ignoring null terminator)
		char toProcess = this->text[i];

		switch (toProcess) {
		case '\n':
			xOffset = 0.0f;
			yOffset -= this->ySpacing * this->pixelSize;
			continue;
		case '\t':
			xOffset += 2 * this->xSpacing;
			continue;
		}

		Character* c = this->font->getCharacter(toProcess, this->pixelSize);

		float xPos = xOffset + c->bearing.x;
		float yPos = yOffset - (c->size.y - c->bearing.y);

		float w = c->size.x;
		float h = c->size.y;

		if (this->autoWrapX) {
			if ((xPos + h) * relScale > this->maxWidth) {
				// move character to a new line and all the way to the left
				xOffset = 0.0f;
				xPos = xOffset + c->bearing.x;

				yOffset -= this->ySpacing * this->pixelSize;
				yPos = yOffset - (c->size.y - c->bearing.y);
			}
		}

		// ignore spaces if first character of line
		if (toProcess == ' ' && xPos == 0.0f) {

		}

		Vertex vs[4] = {
			Vertex {
				vec3(xPos * relScale, yPos * relScale, 0.0f),
				vec2(0.0f, 1.0f)
			},
			Vertex {
				vec3((xPos + w) * relScale, yPos * relScale, 0.0f),
				vec2(1.0f, 1.0f)
			},
			Vertex {
				vec3(xPos * relScale, (yPos + h) * relScale, 0.0f),
				vec2(0.0f, 0.0f)
			},
			Vertex {
				vec3((xPos + w) * relScale, (yPos + h) * relScale, 0.0f),
				vec2(1.0f, 0.0f)
			}
		};

		for (unsigned int j = 0; j < 4; j++) this->vertices.push_back(vs[j]);

		this->textures.push_back(c->tex);

		xOffset += (c->advance >> 6) * this->xSpacing;

		// tell things to actually remesh this renderer
		this->requiresRemeshing = true;
	}
}

vector<byte> TextRenderer::serialise() {
	vector<byte> out;

	unsigned int e = this->type;
	byte* toAdd = reinterpret_cast<byte*>(&e);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(toAdd[i]);
	}

	void* id = this;
	toAdd = reinterpret_cast<byte*>(&id);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(toAdd[i]);
	}

	unsigned int length = this->text.length();
	toAdd = reinterpret_cast<byte*>(&length);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(toAdd[i]);
	}

	for (unsigned int i = 0; i < this->text.length(); i++) {
		char a = this->text.c_str()[i];
		toAdd = reinterpret_cast<byte*>(&a);
		for (unsigned int j = 0; j < sizeof(char); j++) {
			out.push_back(toAdd[j]);
		}
	}

	toAdd = reinterpret_cast<byte*>(&this->fontFile);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->pixelSize);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->xSpacing);
	for (unsigned int i = 0; i < sizeof(float); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->ySpacing);
	for (unsigned int i = 0; i < sizeof(float); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->autoWrapX);
	for (unsigned int i = 0; i < sizeof(bool); i++) {
		out.push_back(toAdd[i]);
	}

	toAdd = reinterpret_cast<byte*>(&this->maxWidth);
	for (unsigned int i = 0; i < sizeof(float); i++) {
		out.push_back(toAdd[i]);
	}

	return out;
}

void TextRenderer::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	unsigned int textLength = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	this->text = "";
	for (unsigned int i = 0; i < textLength; i++) {
		this->text += *reinterpret_cast<char*>(&bytes[position]);
		position += sizeof(char);
	}
	
	// font file asset
	this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
	position += sizeof(void*);

	this->pixelSize = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	this->xSpacing = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);

	this->ySpacing = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);

	this->autoWrapX = *reinterpret_cast<bool*>(&bytes[position]);
	position += sizeof(bool);

	this->maxWidth = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);

	this->deserialisedSize = position;
}