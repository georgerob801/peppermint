#ifndef PPMINT_TILESET_H
#define PPMINT_TILESET_H

#include <peppermint/classes/rendering/TextureSet.h>
#include <vector>

#include <peppermint/classes/Asset.h>

using namespace std;

namespace peppermint {
	namespace rendering {
		/// <summary>
		/// Class for storing tileset information.
		/// </summary>
		class Tileset : public Asset {
		public:
			/// <summary>
			/// Create a Tileset.
			/// </summary>
			Tileset() : Asset(AssetType::TILESET) { }

			// tile coords is centre +- (1/2)(tileset.tileSize)
			
			/// <summary>
			/// Struct containing tile texture mapping data.
			/// </summary>
			struct TileTextureMapping {
				// unsigned int tileType;
				vec2 centre;
			};

			/// <summary>
			/// Vector containing all tile-texture mappings.
			/// </summary>
			vector<TileTextureMapping> textureMappings;

			/// <summary>
			/// The default tile-texture mapping.
			/// </summary>
			TileTextureMapping defaultTextureMapping = {
				.centre = vec2(0.0f, 0.0f)
			};

			/// <summary>
			/// A vector containing pointers to all TextureSets used by this Tileset.
			/// </summary>
			vector<TextureSet*> textureSets;
			/// <summary>
			/// The pixel size of each tile.
			/// </summary>
			vec2 tileSize = vec2(1.0f, 1.0f);

			/// <summary>
			/// Go to a specified TextureSet.
			/// </summary>
			/// <param name="index">The index of the TextureSet to go to.</param>
			void goToTextureSet(int index);
			/// <summary>
			/// Go to the next TextureSet.
			/// </summary>
			void nextTextureSet();
			/// <summary>
			/// Get a pointer to the TextureSet currently in use by this Tileset.
			/// </summary>
			/// <returns>A pointer to the TextureSet currently in use by this Tileset.</returns>
			TextureSet* getCurrentTextureSet();
			/// <summary>
			/// Generate this Tileset's textures.
			/// </summary>
			void generateTextures();

			/// <summary>
			/// Generate all default tile-texture mappings.
			/// </summary>
			void generateDefaultTextureMappings();

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
		private:
			/// <summary>
			/// The index of the TextureSet currently in use.
			/// </summary>
			int currentTextureSet = 0;
		};
	}
}

#endif