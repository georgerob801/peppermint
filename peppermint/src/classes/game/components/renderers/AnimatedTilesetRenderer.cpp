#include <peppermint/classes/game/components/renderers/AnimatedTilesetRenderer.h>

#include <GLFW/glfw3.h>

using namespace peppermint::game::components;

AnimatedTilesetRenderer::AnimatedTilesetRenderer(unsigned int width, unsigned int height) : TilesetRenderer(width, height) {
	this->type = Component::ANIMATED_TILESET_RENDERER;
}

void AnimatedTilesetRenderer::start() {
	this->animationStart = glfwGetTime();
}

void AnimatedTilesetRenderer::loop() {
	vec2 scale = vec2(1.0f / (float)this->tileset->getCurrentTextureSet()->atlas->getWidth(), 1.0f / (float)this->tileset->getCurrentTextureSet()->atlas->getHeight());
	vec2 uvOffset = vec2(0.0f, 0.0f);
	unsigned int texOffset = 0;

	if (this->animations.size() > 0 && this->animations.size() < this->animationIndex - 1) {
		TilesetAnimation* anim = this->animations[this->animationIndex];

		uvOffset = anim->getUVOffsetAtStep(anim->stepAtTime(glfwGetTime() - this->animationStart));
		texOffset = anim->getTextureOffsetAtStep(anim->stepAtTime(glfwGetTime() - this->animationStart));
	}

	this->currentUVOffset = vec2(uvOffset.x * scale.x, uvOffset.y * scale.y);
	this->currentTexOffset = texOffset;
}

vector<byte> AnimatedTilesetRenderer::serialise() {
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

	unsigned int numAnimations = this->animations.size();
	byte* numAnimationsB = reinterpret_cast<byte*>(&numAnimations);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(numAnimationsB[i]);
	}

	for (unsigned int i = 0; i < this->animations.size(); i++) {
		byte* animationIDB = reinterpret_cast<byte*>(&this->animations[i]);
		for (unsigned int j = 0; j < sizeof(void*); j++) {
			out.push_back(animationIDB[j]);
		}
	}

	byte* animationIndexB = reinterpret_cast<byte*>(&this->animationIndex);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(animationIndexB[i]);
	}

	byte* runningB = reinterpret_cast<byte*>(&this->running);
	for (unsigned int i = 0; i < sizeof(bool); i++) {
		out.push_back(runningB[i]);
	}

	return out;
}

void AnimatedTilesetRenderer::deserialise(vector<byte> bytes) {
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

	unsigned int numAnimations = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	for (unsigned int i = 0; i < numAnimations; i++) {
		this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
		position += sizeof(void*);
	}

	this->animationIndex = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	this->running = *reinterpret_cast<bool*>(&bytes[position]);
	position += sizeof(bool);

	this->deserialisedSize = position;
}