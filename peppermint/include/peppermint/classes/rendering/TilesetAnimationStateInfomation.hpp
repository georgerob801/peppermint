#ifndef PPMINT_TILESET_ANIMATION_STATE_INFORMATION_H
#define PPMINT_TILESET_ANIMATION_STATE_INFORMATION_H

#include <glm/glm.hpp>

using namespace glm;

// used as an interface
namespace peppermint {
	namespace rendering {
		class TilesetAnimationStateInformation {
		public:
			vec2 getUVOffset() {
				return this->currentUVOffset;
			}

			int getTexOffset() {
				return this->currentTexOffset;
			}
		protected:
			vec2 currentUVOffset;
			int currentTexOffset;
		};
	}
}

#endif