#ifndef PPMINT_TILESET_H
#define PPMINT_TILESET_H

#include <peppermint/classes/rendering/TextureSet.h>
#include <vector>

using namespace std;

namespace peppermint {
	namespace rendering {
		class Tileset {
		public:
			vector<TextureSet> textureSets;
			float tileSize = 1.0f;

			void goToTextureSet(int index);
			void nextTextureSet();
			int getCurrentTextureSet();
		private:
			int currentTextureSet = 0;
		};
	}
}

#endif