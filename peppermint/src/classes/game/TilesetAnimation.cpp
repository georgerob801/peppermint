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

	void* id = this;
	byte* idB = reinterpret_cast<byte*>(&id);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(idB[i]);
	}

	unsigned int typeCast = (unsigned int)this->type;
	byte* typeB = reinterpret_cast<byte*>(&typeCast);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(typeB[i]);
	}

	unsigned int length = 0;
	byte* pathSizeB = reinterpret_cast<byte*>(&length);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(pathSizeB[i]);
	}

	vector<byte*> intsToAdd;

	intsToAdd.push_back(reinterpret_cast<byte*>(&this->start));
	intsToAdd.push_back(reinterpret_cast<byte*>(&this->step));
	intsToAdd.push_back(reinterpret_cast<byte*>(&this->end));
	intsToAdd.push_back(reinterpret_cast<byte*>(&this->texStartOffset));
	intsToAdd.push_back(reinterpret_cast<byte*>(&this->texStepOffset));

	for (unsigned int i = 0; i < intsToAdd.size(); i++) {
		for (unsigned int j = 0; j < sizeof(int); j++) {
			out.push_back(intsToAdd[i][j]);
		}
	}

	vector<byte*> floatsToAdd;

	floatsToAdd.push_back(reinterpret_cast<byte*>(&this->stepTime));
	floatsToAdd.push_back(reinterpret_cast<byte*>(&this->uvStartOffset.x));
	floatsToAdd.push_back(reinterpret_cast<byte*>(&this->uvStartOffset.y));
	floatsToAdd.push_back(reinterpret_cast<byte*>(&this->uvStepOffset.x));
	floatsToAdd.push_back(reinterpret_cast<byte*>(&this->uvStepOffset.y));

	for (unsigned int i = 0; i < floatsToAdd.size(); i++) {
		for (unsigned int j = 0; j < sizeof(float); j++) {
			out.push_back(floatsToAdd[i][j]);
		}
	}



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