#include <peppermint/classes/game/TilesetAnimation.h>

using namespace peppermint::game;

int TilesetAnimation::stepAtTime(double time) {
	return ((int)floor(time / this->stepTime) * this->step) % (this->end + 1);
}

vec2 TilesetAnimation::getUVOffsetAtStep(int step) {
	return this->uvStartOffset + vec2(step * this->uvStepOffset.x, step * this->uvStepOffset.y);
}

int TilesetAnimation::getTextureOffsetAtStep(int step) {
	return this->texStartOffset + (step * this->texStepOffset);
}