#ifndef PPMINT_TEXTURE_H
#define PPMINT_TEXTURE_H

namespace peppermint {
	namespace rendering {
		class Texture {
		public:
			unsigned char* data;

			Texture();
			Texture(char* path);

			int getWidth();
			int getHeight();
			int getNrChannels();
			void bind();
		private:
			int width;
			int height;
			int nrChannels;

			unsigned int glTextureLocation;
		};
	}
}

#endif