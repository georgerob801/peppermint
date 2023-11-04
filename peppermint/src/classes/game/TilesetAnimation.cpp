#include <peppermint/classes/game/TilesetAnimation.h>

#include <format>

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

vector<byte> TilesetAnimation::serialise() {
	vector<byte> out;

	//out += "TilesetAnimation:\n";
	//out += "Data:\n";
	//out += std::format("Start: {}\n", this->start);
	//out += std::format("Step: {}\n", this->step);
	//out += std::format("End: {}\n", this->end);

	//out += std::format("StepTime: {}\n", this->stepTime);

	//out += std::format("UVStartOffset.x: {}\n", this->uvStartOffset.x);
	//out += std::format("UVStartOffset.y: {}\n", this->uvStartOffset.y);

	//out += std::format("UVStepOffset.x: {}\n", this->uvStepOffset.x);
	//out += std::format("UVStepOffset.y: {}\n", this->uvStepOffset.y);

	//out += std::format("TexStartOffset: {}\n", this->texStartOffset);
	//out += std::format("TexStepOffset: {}\n", this->texStepOffset);

	return out;
}

void TilesetAnimation::deserialise(vector<byte> bytes) {

}