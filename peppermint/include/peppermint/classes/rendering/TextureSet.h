#ifndef PPMINT_TEXTURE_SET_H
#define PPMINT_TEXTURE_SET_H

#include <peppermint/classes/rendering/Texture.h>
#include <vector>
#include <glm/glm.hpp>

#include <peppermint/classes/Asset.h>

using namespace std;
using namespace glm;

// WILL CONTAIN UTILITIES FOR MAKING TEXTURE ATLASES

namespace peppermint {
	namespace rendering {
		/// <summary>
		/// Class for creating and using texture atlases.
		/// </summary>
		class TextureSet : public Asset {
		public:
			/// <summary>
			/// Create a new TextureSet.
			/// </summary>
			TextureSet() : Asset(AssetType::TEXTURE_SET) { }

			/// <summary>
			/// A vector containing all the Textures this TextureSet uses.
			/// </summary>
			vector<Texture*> textures;
			/// <summary>
			/// A pointer to this TextureSet's texture atlas.
			/// </summary>
			Texture* atlas = nullptr;

			/// <summary>
			/// Add a Texture to this TextureSet.
			/// </summary>
			/// <param name="tex">A pointer to the Texture to add.</param>
			void addTexture(Texture* tex);
			/// <summary>
			/// Generate a texture atlas for this TextureSet.
			/// </summary>
			void generateAtlas();
			/// <summary>
			/// Map UV coordinates on an original image to UV coordinates on a texture atlas.
			/// </summary>
			/// <param name="tex">A pointer to the original Texture.</param>
			/// <param name="uv">The original UV coordinates.</param>
			/// <returns>The mapped UV coordinates.</returns>
			vec2 mapUVToAtlas(Texture* tex, vec2 uv);

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
		private:
			/// <summary>
			/// True/false depending on whether the texture atlas needs to be generated.
			/// </summary>
			bool requiresAtlasGeneration = true;
		};
	}
}

#endif