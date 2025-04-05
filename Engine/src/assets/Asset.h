#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace rl
{

    using Asset = size_t;

    using Mesh = Asset;
    using Texture = Asset;

    enum class AssetType : uint8_t
    {
        Unknown = 0,
        Scene = 1,
        Mesh = 2,
        Component = 3,
        System = 4,
        Folder = 5,
        //Texture = 3,
        //Audio = 4,
        // ...
    };

    static std::string AssetTypeToString(AssetType type)
    {
        switch (type) {
            case AssetType::Unknown:
                return "Unknown";
            case AssetType::Scene:
                return "Scene";
            case AssetType::Mesh:
                return "Mesh";
            case AssetType::System:
                return "System (C++)";
            case AssetType::Component:
                return "Component (C++)";
            case AssetType::Folder:
                return "Folder";
            default:
                return "ERROR";
        }
    }

    class AssetData
    {
    public:
        virtual ~AssetData() = default;

        static std::shared_ptr<AssetData> CreateAsset(const std::filesystem::path& location, const std::string& name, AssetType type, Asset id);
        static std::shared_ptr<AssetData> ImportFromFile(const std::filesystem::path& file, Asset id);
        static std::shared_ptr<AssetData> OpenAssetFile(const std::filesystem::path& file);

        void Save();
        void WriteAssetFile(const std::filesystem::path& location, const std::string& name);
        void CheckForUpdates(const std::filesystem::path& file);

        inline Asset GetID() const
        {
            return id;
        }

    protected:
        virtual void ImportFile(const std::filesystem::path& file) = 0;
        virtual void ReadFile(std::ifstream& input) = 0;
        virtual void WriteData(std::ofstream& output) = 0;

        Asset id;
        AssetType type = AssetType::Unknown;
        std::filesystem::path file;
    };
}
