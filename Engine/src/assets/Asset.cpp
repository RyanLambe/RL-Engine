#include "Asset.h"

#include <fstream>
#include <memory>

#include "../core/Logger.h"
#include "Mesh.h"

namespace rl
{

    std::shared_ptr<Asset> Asset::CreateAsset(const std::filesystem::path& location, const std::string& name)
    {
        RL_LOG_ERROR("Unable to create asset. Unknown file type: ");
        return nullptr;
    }

    std::shared_ptr<Asset> Asset::ImportAsset(const std::filesystem::path& file)
    {
        const auto ext = file.extension().string();
        if (ext == ".fbx" || ext == ".obj")
        {
            std::shared_ptr<Asset> out = std::static_pointer_cast<Asset>(std::make_shared<Mesh>());
            out->ImportFile(file);
            out->type = AssetType::Mesh;
            out->lastModified = last_write_time(file);
            return out;
        }

        RL_LOG_ERROR("Unable to import file. Unknown file type: ", ext);
        return nullptr;
    }

    std::shared_ptr<Asset> Asset::OpenAssetFile(const std::filesystem::path& file)
    {
        return nullptr;
    }

    void Asset::WriteAssetFile(const std::filesystem::path& location, const std::string& name)
    {
        std::filesystem::path file = location / (name + ".asset");

        std::ofstream output;
        output.open(file, std::ios::binary);
        if (!output.is_open())
        {
            RL_LOG_ERROR("unable to open file");
            return;
        }

        output << "RL";
        output << (uint8_t)type;

        int64_t tempTime = lastModified.time_since_epoch().count();
        output.write((char*)&tempTime, sizeof(int64_t));

        WriteData(output);

        output.close();
    }

    void Asset::CheckForUpdates(const std::filesystem::path& file) {}
}