#ifndef PPMINT_ASSET_H
#define PPMINT_ASSET_H

#include <peppermint/Serialisable.h>

namespace peppermint {
	class Asset : public Serialisable {
	public:
		char* path;
		unsigned int id = NULL;

		enum ASSET_TYPE {
			IMAGE,
			TILESET_ANIMATION,
			FRAGMENT_SHADER_SOURCE,
			VERTEX_SHADER_SOURCE,
			TEXTURE_SET,
			TEXTURE,
			TILESET
		};

		ASSET_TYPE type;

		Asset(ASSET_TYPE type);
		void setPath(char* path);
		void setPath(const char* path);

		vector<byte> serialise();
		void deserialise(vector<byte> bytes);
	};
}

#endif