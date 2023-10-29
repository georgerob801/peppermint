#include <peppermint/classes/rendering/TextureSet.h>

using namespace peppermint::rendering;

// TODO: write this function
void TextureSet::generateAtlas() {
	if (this->requiresAtlasGeneration) this->atlas = this->textures[0];
}