#ifndef PPMINT_COMPONENT_SPRITE_RENDERER_H
#define PPMINT_COMPONENT_SPRITE_RENDERER_H

#include <peppermint-preview/classes/game/components/renderers/Renderer.h>
#include <peppermint-preview/classes/rendering/TextureSet.h>

#include <glm/glm.hpp>

using namespace glm;

namespace peppermint {
	namespace game {
		namespace components {
			/// <summary>
			/// Component that allows rendering of static sprites.
			/// </summary>
			class SpriteRenderer : public Renderer {
			public:
				/// <summary>
				/// Create a new SpriteRenderer.
				/// </summary>
				SpriteRenderer();

				/// <summary>
				/// A pointer to the TextureSet this component uses.
				/// </summary>
				TextureSet* textureSet;
				
				/// <summary>
				/// The pixel position of the centre of the sprite to draw.
				/// </summary>
				vec2 position = vec2(0.5f, 0.5f);
				/// <summary>
				/// The pixel size of the sprite to draw.
				/// </summary>
				vec2 size = vec2(1, 1);

				void generateVertices();
				void generateTextures();

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			private:

			};
		}
	}
}

#endif