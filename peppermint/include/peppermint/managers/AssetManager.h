#ifndef PPMINT_ASSET_MANAGER_H
#define PPMINT_ASSET_MANAGER_H

#include <peppermint/Serialisable.h>
#include <peppermint/classes/Asset.h>
#include <vector>

namespace peppermint {
	namespace managers {
		class AssetManager : public Serialisable {
		public:
			std::vector<Asset*> assets;

			~AssetManager();

			Asset* newAsset(Asset::ASSET_TYPE type);
			void registerAsset(Asset* asset);
			void unregisterAsset(Asset* asset);
			void unregisterAsset(unsigned int id);

			void saveAssetFile(char* filename);
			void saveAssetFile(const char* filename);

			void loadAssetFile(char* filename);
			void loadAssetFile(const char* filename);

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
		private:
			static unsigned int currentId;
		};
	}
}

#endif