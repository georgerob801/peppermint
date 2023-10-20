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
				Tileset tileset;
				vector<Mesh> meshes;
			private:

			};
		}
	}
}

#endif