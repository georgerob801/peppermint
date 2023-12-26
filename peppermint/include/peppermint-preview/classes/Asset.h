#ifndef PPMINT_ASSET_H
#define PPMINT_ASSET_H

#include <peppermint-preview/Serialisable.h>

namespace peppermint {
	/// <summary>
	/// Class for storing information related to required files.
	/// </summary>
	class Asset : public Serialisable {
	public:
		/// <summary>
		/// The path to this Asset's file.
		/// </summary>
		char* path;

		/// <summary>
		/// Enum to determing types of Assets.
		/// </summary>
		enum AssetType {
			NONE,
			IMAGE,
			TILESET_ANIMATION,
			FRAGMENT_SHADER_SOURCE,
			VERTEX_SHADER_SOURCE,
			TEXTURE_SET,
			TEXTURE,
			TILESET,
			PPMINT_WORLD_FILE,
			PPMINT_GAME_FILE,
			PPMINT_ASSET_FILE,
			SOUND,
			FONT,
			SHADER
		};

		/// <summary>
		/// The type of this Asset.
		/// </summary>
		AssetType type;

		/// <summary>
		/// Create a new Asset.
		/// </summary>
		/// <param name="type">The type of Asset to create.</param>
		Asset(AssetType type);
		/// <summary>
		/// Create a new Asset.
		/// </summary>
		/// <param name="type">The type of Asset to create.</param>
		/// <param name="path">The path of the Asset.</param>
		Asset(AssetType type, char* path);

		/// <summary>
		/// Set this Asset's path.
		/// </summary>
		/// <param name="path">The path to set.</param>
		void setPath(char* path);
		/// <summary>
		/// Set this Asset's path.
		/// </summary>
		/// <param name="path">The path to set.</param>
		void setPath(const char* path);

		vector<byte> serialise();
		void deserialise(vector<byte> bytes);
	};
}

#endif