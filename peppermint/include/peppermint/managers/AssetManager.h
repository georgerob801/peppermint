#ifndef PPMINT_ASSET_MANAGER_H
#define PPMINT_ASSET_MANAGER_H

#include <peppermint/Serialisable.h>
#include <peppermint/classes/Asset.h>
#include <vector>

namespace peppermint {
	namespace managers {
		/// <summary>
		/// Class for managing Assets.
		/// </summary>
		class AssetManager : public Serialisable {
		public:
			/// <summary>
			/// A vector containing pointers to all Assets used by this AssetManager.
			/// </summary>
			std::vector<Asset*> assets;

			/// <summary>
			/// Destroy this AssetManager and all Assets attached to it.
			/// </summary>
			~AssetManager();

			/// <summary>
			/// Create and register a new Asset.
			/// </summary>
			/// <param name="type">The type of Asset to create.</param>
			/// <returns>A pointer to the new Asset.</returns>
			Asset* newAsset(Asset::ASSET_TYPE type);
			/// <summary>
			/// Register an Asset.
			/// </summary>
			/// <param name="asset">A pointer to the Asset to register.</param>
			void registerAsset(Asset* asset);
			/// <summary>
			/// Unregister an Asset.
			/// </summary>
			/// <param name="asset">A pointer to the Asset to unregister.</param>
			void unregisterAsset(Asset* asset);

			/// <summary>
			/// Save an Asset.
			/// </summary>
			void saveAssetFile();

			/// <summary>
			/// Load an asset file.
			/// </summary>
			/// <param name="assetFileIn">The asset file Asset.</param>
			void loadAssetFile(Asset* assetFileIn);

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
			/// <summary>
			/// This AssetManager's asset file Asset.
			/// </summary>
			Asset* assetFileAsset;
		private:
			/// <summary>
			/// Deprecated - was used for determining Asset IDs.
			/// </summary>
			static unsigned int currentId;
		};
	}
}

#endif