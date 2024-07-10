#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace rl
{

    enum class AssetType : uint8_t
    {
        Unknown = 0,
        Mesh = 1,
        //Texture = 2,
        //Audio = 3,
        // ...
    };

    class Asset
    {
    public:
        virtual ~Asset() = default;

        static std::shared_ptr<Asset> CreateAsset(const std::filesystem::path& location, const std::string& name);
        static std::shared_ptr<Asset> ImportAsset(const std::filesystem::path& file);
        static std::shared_ptr<Asset> OpenAssetFile(const std::filesystem::path& file);

        void WriteAssetFile(const std::filesystem::path& location, const std::string& name);
        void CheckForUpdates(const std::filesystem::path& file);

    protected:
        virtual void ImportFile(const std::filesystem::path& file) = 0;
        virtual void ReadFile(std::ifstream& input) = 0;
        virtual void WriteData(std::ofstream& output) = 0;

        AssetType type = AssetType::Unknown;
        std::chrono::time_point<std::filesystem::_File_time_clock> lastModified;
    };
}
