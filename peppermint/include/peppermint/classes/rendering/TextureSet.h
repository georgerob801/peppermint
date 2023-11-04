#ifndef PPMINT_TEXTURE_SET_H
#define PPMINT_TEXTURE_SET_H

#include <peppermint/classes/rendering/Texture.h>
#include <vector>
#include <glm/glm.hpp>

#include <peppermint/classes/Asset.h>

using namespace std;
using namespace glm;

// WILL CONTAIN UTILITIES FOR MAKING TEXTURE ATLASES

namespace peppermint {
	namespace rendering {
		class TextureSet : public Asset {
		public:
			TextureSet() : Asset(ASSET_TYPE::TEXTURE_SET) { }

			vector<Texture*> textures;
			Texture* atlas = nullptr;

			void addTexture(Texture* tex);
			void generateAtlas();
			vec2 mapUVToAtlas(vec2 uv);

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
		private:
			bool requiresAtlasGeneration = true;
		};
	}
}

#endif