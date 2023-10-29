#ifndef PPMINT_COMPONENT_TILESET_RENDERER_H
#define PPMINT_COMPONENT_TILESET_RENDERER_H

#include <peppermint/classes/game/components/renderers/Renderer.h>
#include <peppermint/classes/rendering/Mesh.h>
#include <peppermint/classes/rendering/Tileset.h>
#include <peppermint/classes/game/components/NavigableMap.hpp>
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
				void generateTextures();
			private:
				unsigned int width;
				unsigned int height;
			};
		}
	}
}

#endif