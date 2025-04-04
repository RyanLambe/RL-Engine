#include "AssetManager.h"

namespace rl
{
    Asset AssetManager::ImportFromFile(const std::filesystem::path &file) {
        assetMap[nextAsset] = AssetData::ImportFromFile(file, nextAsset);
        if(assetMap[nextAsset] == nullptr)
            return 0;
        nextAsset++;
        return nextAsset - 1;
    }

    Asset AssetManager::CreateAsset(const std::filesystem::path& location, const std::string& name, AssetType type) {
        assetMap[nextAsset] = AssetData::CreateAsset(location, name, type, nextAsset);
        if(assetMap[nextAsset] == nullptr)
            return 0;
        nextAsset++;
        return nextAsset - 1;
    }

    Asset AssetManager::OpenAssetFile(const std::filesystem::path &file) {
        std::shared_ptr<AssetData> data = AssetData::OpenAssetFile(file);
        assetMap[data->GetID()] = data;
        return data->GetID();
    }
}