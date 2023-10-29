#include <peppermint/classes/game/components/renderers/BasicPlayerRenderer.h>

#include <GLFW/glfw3.h>

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