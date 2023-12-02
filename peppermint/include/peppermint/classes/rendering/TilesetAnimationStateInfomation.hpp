#ifndef PPMINT_TILESET_ANIMATION_STATE_INFORMATION_H
#define PPMINT_TILESET_ANIMATION_STATE_INFORMATION_H

#include <glm/glm.hpp>

using namespace glm;

// used as an interface
namespace peppermint {
	namespace rendering {
		/// <summary>
		/// Interface for tilesets that can be animated.
		/// </summary>
		class TilesetAnimationStateInformation {
		public:
			/// <summary>
			/// Get the current UV offset of this Tileset.
			/// </summary>
			/// <returns></returns>
			vec2 getUVOffset() {
				return this->currentUVOffset;
			}

			/// <summary>
			/// Get the current TextureSet offset of this Tileset.
			/// </summary>
			/// <returns></returns>
			int getTexOffset() {
				return this->currentTexOffset;
			}
		protected:
			/// <summary>
			/// The current UV offset of this Tileset.
			/// </summary>
			vec2 currentUVOffset;
			/// <summary>
			/// THe current TextureSet offset of this Tileset.
			/// </summary>
			int currentTexOffset;
		};
	}
}

#endif