#ifndef PPMINT_TEXTURE_SET_H
#define PPMINT_TEXTURE_SET_H

#include <peppermint/classes/rendering/Texture.h>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

// WILL CONTAIN UTILITIES FOR MAKING TEXTURE ATLASES

namespace peppermint {
	namespace rendering {
		class TextureSet {
		public:
			vector<Texture> textures;
			Texture atlas;

			void addTexture(Texture tex);
			void generateAtlas();
			vec2 mapUVToAtlas(vec2 uv);
		private:

		};
	}
}

#endif