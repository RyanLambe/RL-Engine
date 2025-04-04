#pragma once

#include <unordered_map>
#include <filesystem>

#include "Asset.h"

namespace rl
{
    class AssetManager
    {
    public:

        inline std::shared_ptr<AssetData> GetAssetData(Asset asset)
        {
            return assetMap[asset];
        }

        [[nodiscard]] inline bool IsAssetLoaded(Asset asset) const
        {
            return assetMap.contains(asset);
        }

        Asset ImportFromFile(const std::filesystem::path& file);

        Asset CreateAsset(const std::filesystem::path& location, const std::string& name, AssetType type);

        Asset OpenAssetFile(const std::filesystem::path& file);

        inline void UnloadAsset(Asset asset)
        {
            assetMap.erase(asset);
        }

    private:
        std::unordered_map<Asset, std::shared_ptr<AssetData>> assetMap = {};
        Asset nextAsset = 1;
    };
}
