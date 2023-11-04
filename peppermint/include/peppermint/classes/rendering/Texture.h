#ifndef PPMINT_TEXTURE_H
#define PPMINT_TEXTURE_H

#include <peppermint/classes/Asset.h>

namespace peppermint {
	namespace rendering {
		class Texture : public Asset {
		public:
			Texture();
			Texture(Asset* asset);

			int getWidth();
			int getHeight();
			int getNrChannels();
			void bind();

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
		private:
			int width;
			int height;
			int nrChannels;

			Asset* imageAsset = nullptr;

			unsigned int glTextureLocation = NULL;
		};
	}
}

#endif