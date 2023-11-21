#ifndef PPMINT_ASSET_H
#define PPMINT_ASSET_H

#include <peppermint/Serialisable.h>

namespace peppermint {
	class Asset : public Serialisable {
	public:
		char* path;

		enum ASSET_TYPE {
			NONE,
			IMAGE,
			TILESET_ANIMATION,
			FRAGMENT_SHADER_SOURCE,
			VERTEX_SHADER_SOURCE,
			TEXTURE_SET,
			TEXTURE,
			TILESET,
			PPMINT_WORLD_FILE
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