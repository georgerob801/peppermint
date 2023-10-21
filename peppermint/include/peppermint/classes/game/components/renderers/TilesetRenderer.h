#ifndef PPMINT_COMPONENT_TILESET_RENDERER_H
#define PPMINT_COMPONENT_TILESET_RENDERER_H

#include <peppermint/classes/game/components/renderers/Renderer.h>
#include <peppermint/classes/rendering/Mesh.h>
#include <peppermint/classes/rendering/Tileset.h>
#include <vector>

using namespace peppermint::rendering;

namespace peppermint {
	namespace game {
		namespace components {
			class TilesetRenderer : public Renderer {
			public:
				TilesetRenderer(unsigned int width, unsigned int height);
				~TilesetRenderer();
				void awake();

				bool requiresRemesh = true;

				Tileset* tileset;

				unsigned int* tileTypes;

				void generateVertices();

				// tile coords is centre +- (1/2)(tileset.tileSize)
				struct TileTextureMapping {
					// unsigned int tileType;
					vec2 centre;
				};

				vector<TileTextureMapping> textureMappings;

				TileTextureMapping defaultTextureMapping = {
					.centre = vec2(0.0f, 0.0f)
				};
			private:
				unsigned int width;
				unsigned int height;
			};
		}
	}
}

#endif