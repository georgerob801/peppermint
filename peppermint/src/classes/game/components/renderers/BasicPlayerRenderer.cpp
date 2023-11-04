#include <peppermint/classes/game/components/renderers/BasicPlayerRenderer.h>

#include <GLFW/glfw3.h>
#include <format>

using namespace peppermint::game::components;

BasicPlayerRenderer::BasicPlayerRenderer(unsigned int width, unsigned int height) : TilesetRenderer(width, height) {

}

void BasicPlayerRenderer::start() {
	this->animationStart = glfwGetTime();
}

// this logic is so unbelievably cursed but somehow works so i'm not touching it
void BasicPlayerRenderer::loop() {
	vec2 scale = vec2(1.0f / (float)this->tileset->getCurrentTextureSet()->atlas->getWidth(), 1.0f / (float)this->tileset->getCurrentTextureSet()->atlas->getHeight());
	vec2 offset;
	auto cps = this->pc->getActiveKeys();

	if (this->pc->currentlyMoving.forward) {
		if (this->animationStart == 0) {
			this->animationStart = glfwGetTime();
		}

		offset = this->up->getUVOffsetAtStep(this->up->stepAtTime(glfwGetTime() - this->animationStart));
		
	} else if (this->pc->currentlyMoving.backward) {
		if (this->animationStart == 0) {
			this->animationStart = glfwGetTime();
		}

		offset = this->down->getUVOffsetAtStep(this->down->stepAtTime(glfwGetTime() - this->animationStart));
		
	} else if (this->pc->currentlyMoving.left) {
		if (this->animationStart == 0) {
			this->animationStart = glfwGetTime();
		}

		offset = this->left->getUVOffsetAtStep(this->left->stepAtTime(glfwGetTime() - this->animationStart));
		
	} else if (this->pc->currentlyMoving.right) {
		if (this->animationStart == 0) {
			this->animationStart = glfwGetTime();
		}

		offset = this->right->getUVOffsetAtStep(this->right->stepAtTime(glfwGetTime() - this->animationStart));
		
	} else {
		if ((!cps.forward && !cps.backward && !cps.left && !cps.right) || this->pc->attemptingCollidingMove) this->animationStart = 0;

		switch (this->pc->facing) {
		case PlayerController::UP:
			offset = this->up->getUVOffsetAtStep(this->up->stepAtTime(this->animationStart ? glfwGetTime() - this->animationStart : 0));
			break;
		case PlayerController::LEFT:
			offset = this->left->getUVOffsetAtStep(this->left->stepAtTime(this->animationStart ? glfwGetTime() - this->animationStart : 0));
			break;
		case PlayerController::RIGHT:
			offset = this->right->getUVOffsetAtStep(this->right->stepAtTime(this->animationStart ? glfwGetTime() - this->animationStart : 0));
			break;
		default:
		case PlayerController::DOWN:
			offset = this->down->getUVOffsetAtStep(this->down->stepAtTime(this->animationStart ? glfwGetTime() - this->animationStart : 0));
			break;
		}
	}

	this->currentUVOffset = vec2(offset.x * scale.x, offset.y * scale.y);
}

vector<byte> BasicPlayerRenderer::serialise() {
	vector<byte> out;

	unsigned int e = this->type;
	byte* toAdd = (byte*)reinterpret_cast<char*>(&e);

	for (unsigned int i = 0; i < sizeof(unsigned int) / sizeof(byte); i++) {
		out.push_back(toAdd[i]);
	}

	void* id = this;
	byte* toAdd2 = (byte*)reinterpret_cast<char*>(&id);

	for (unsigned int i = 0; i < sizeof(id) / sizeof(byte); i++) {
		out.push_back(toAdd2[i]);
	}

	vector<byte*> pointersToAdd;

	pointersToAdd.push_back(reinterpret_cast<byte*>(&this->pc));
	pointersToAdd.push_back(reinterpret_cast<byte*>(&this->up));
	pointersToAdd.push_back(reinterpret_cast<byte*>(&this->down));
	pointersToAdd.push_back(reinterpret_cast<byte*>(&this->left));
	pointersToAdd.push_back(reinterpret_cast<byte*>(&this->right));

	for (unsigned int i = 0; i < pointersToAdd.size(); i++) {
		for (unsigned int j = 0; j < sizeof(void*); j++) {
			out.push_back(pointersToAdd[i][j]);
		}
	}

	//out += "Component:\n";
	//out += "Type: BasicPlayerRenderer\n";
	//out += "Data:\n";

	//out += std::format("PlayerController: {}\n", (void*)this->pc);
	//out += std::format("Up: {}\n", (void*)this->up);
	//out += std::format("Down: {}\n", (void*)this->down);
	//out += std::format("Left: {}\n", (void*)this->left);
	//out += std::format("Right: {}\n", (void*)this->right);

	return out;
}

void BasicPlayerRenderer::deserialise(vector<byte> bytes) {

}