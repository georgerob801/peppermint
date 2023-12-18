#ifndef PPMINT_TEXTURE_H
#define PPMINT_TEXTURE_H

#include <peppermint/classes/Asset.h>

namespace peppermint {
	namespace rendering {
		/// <summary>
		/// Class for texture information.
		/// </summary>
		class Texture : public Asset {
		public:
			/// <summary>
			/// Create a new Texture.
			/// </summary>
			Texture();
			/// <summary>
			/// Create a new Texture.
			/// </summary>
			/// <param name="asset">The image Asset to use.</param>
			Texture(Asset* asset);

			/// <summary>
			/// Destroy this texture.
			/// </summary>
			~Texture();

			/// <summary>
			/// Get the width of this Texture.
			/// </summary>
			/// <returns>The width of this Texture.</returns>
			int getWidth();
			/// <summary>
			/// Get the height of this Texture.
			/// </summary>
			/// <returns>The height of this Texture.</returns>
			int getHeight();
			/// <summary>
			/// Get the number of channels in this Texture.
			/// </summary>
			/// <returns>The number of channels in this Texture.</returns>
			int getNrChannels();
			/// <summary>
			/// Use this Texture.
			/// </summary>
			void bind();
			/// <summary>
			/// Load this Texture from its current image Asset.
			/// </summary>
			void loadFromAsset();
			/// <summary>
			/// Set this Texture's image Asset.
			/// </summary>
			/// <param name="image">The image Asset to use.</param>
			void setImageAsset(Asset* image);

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
		private:
			/// <summary>
			/// This Texture's width.
			/// </summary>
			int width;
			/// <summary>
			/// This Texture's height.
			/// </summary>
			int height;
			/// <summary>
			/// This Texture's number of channels.
			/// </summary>
			int nrChannels;

			/// <summary>
			/// A pointer to the image Asset this Texture uses.
			/// </summary>
			Asset* imageAsset = nullptr;

			/// <summary>
			/// The OpenGL ID of this texture.
			/// </summary>
			unsigned int glTextureLocation = NULL;
		};
	}
}

#endif