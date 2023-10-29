#ifndef PPMINT_TILESET_H
#define PPMINT_TILESET_H

#include <peppermint/classes/rendering/TextureSet.h>
#include <vector>

using namespace std;

namespace peppermint {
	namespace rendering {
		class Tileset {
		public:
			// tile coords is centre +- (1/2)(tileset.tileSize)
			struct TileTextureMapping {
				// unsigned int tileType;
				vec2 centre;
			};

			vector<TileTextureMapping> textureMappings;

			TileTextureMapping defaultTextureMapping = {
				.centre = vec2(0.0f, 0.0f)
			};

			vector<TextureSet*> textureSets;
			vec2 tileSize = vec2(1.0f, 1.0f);

			void goToTextureSet(int index);
			void nextTextureSet();
			TextureSet* getCurrentTextureSet();
			void generateTextures();
		private:
			int currentTextureSet = 0;
		};
	}
}

#endif