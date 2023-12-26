#ifndef PPMINT_COMPONENT_TILESET_RENDERER_H
#define PPMINT_COMPONENT_TILESET_RENDERER_H

#include <peppermint-preview/classes/game/components/renderers/Renderer.h>
#include <peppermint-preview/classes/rendering/Mesh.h>
#include <peppermint-preview/classes/rendering/Tileset.h>
#include <peppermint-preview/classes/game/components/NavigableMap.hpp>
#include <vector>

using namespace peppermint::rendering;

namespace peppermint {
	namespace game {
		namespace components {
			/// <summary>
			/// Component that allows the rendering of static tilesets.
			/// </summary>
			class TilesetRenderer : public Renderer {
			public:
				/// <summary>
				/// Create a new TilesetRenderer.
				/// </summary>
				/// <param name="width">The width of the desired tileset.</param>
				/// <param name="height">The height of the desired tileset.</param>
				TilesetRenderer(unsigned int width, unsigned int height);
				/// <summary>
				/// Destroy a TilesetRenderer.
				/// </summary>
				~TilesetRenderer();
				void awake();

				bool requiresRemesh = true;

				/// <summary>
				/// A pointer to the Tileset asset this TilesetRenderer uses.
				/// </summary>
				Tileset* tileset;

				/// <summary>
				/// A pointer to the first tile type value of this TilesetRenderer. These values correspond to the TilesetMappings in the Tileset class.
				/// </summary>
				unsigned short* tileTypes;

				/// <summary>
				/// Set a tile type at a specific location.
				/// </summary>
				/// <param name="x">The x coordinate of the tile to set.</param>
				/// <param name="y">The y coordinate of the tile to set.</param>
				/// <param name="value">The tile type to set the tile to.</param>
				void setTileAt(unsigned int x, unsigned int y, unsigned short value);

				void generateVertices();
				void generateTextures();

				/// <summary>
				/// Fill the entire TilesetRenderer with a specific tile type.
				/// </summary>
				/// <param name="value">The tile type to set all tiles to.</param>
				void fill(unsigned short value);

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);
			private:
			protected:
				/// <summary>
				/// The width of this TilesetRenderer.
				/// </summary>
				unsigned int width;
				/// <summary>
				/// The height of this TilesetRenderer.
				/// </summary>
				unsigned int height;
			};
		}
	}
}

#endif