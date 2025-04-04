#include "Asset.h"

#include <fstream>
#include <memory>

#include "../core/Application.h"
#include "../core/Logger.h"
#include "../files/FileParser.h"
#include "Mesh.h"

namespace rl
{

    std::shared_ptr<AssetData> AssetData::CreateAsset(const std::filesystem::path& location, const std::string& name, AssetType type, Asset id)
    {
        std::string temp = "";
        switch(type)
        {
            case AssetType::Scene:
                RL_LOG(location.lexically_normal().string() + '\\' + name + ".scene");
                if(Application::GetSceneManager().IsSceneOpen())
                    temp = Application::GetSceneManager().GetCurrentScene().GetName();
                Application::GetSceneManager().NewScene(location.lexically_normal().string() + '\\' + name + ".scene");
                Application::GetSceneManager().SetScene(name);
                Application::GetSceneManager().SaveScene();
                if(!temp.empty())
                    Application::GetSceneManager().SetScene(temp);
                return nullptr;
            case AssetType::Unknown:
                return nullptr;
            case AssetType::Mesh:
                return nullptr;
            case AssetType::Component:
                RL_LOG("CREATED Component TEST");
                std::filesystem::copy_file("./templates/Component.cpp", location / (name + ".cpp"));
                std::filesystem::copy_file("./templates/Component.h", location / (name + ".h"));

                FileParser::ReplaceKeyword(location / (name + ".cpp"), "%NAME%", name);
                FileParser::ReplaceKeyword(location / (name + ".h"), "%NAME%", name);
                return nullptr;
            case AssetType::System:
                std::filesystem::copy_file("./templates/System.cpp", location / (name + ".cpp"));
                std::filesystem::copy_file("./templates/System.h", location / (name + ".h"));

                FileParser::ReplaceKeyword(location / (name + ".cpp"), "%NAME%", name);
                FileParser::ReplaceKeyword(location / (name + ".h"), "%NAME%", name);
                return nullptr;
        }
        RL_LOG_ERROR("Unable to create asset. Unknown file type: ", (u64)type);
        return nullptr;
    }

    std::shared_ptr<AssetData> AssetData::ImportFromFile(const std::filesystem::path& file, Asset id)
    {
        const auto ext = file.extension().string();
        if (ext == ".fbx" || ext == ".obj")
        {
            std::shared_ptr<AssetData> out = std::static_pointer_cast<AssetData>(std::make_shared<MeshData>());
            out->id = id;
            out->file = std::filesystem::path(file.string() + ".asset");
            out->type = AssetType::Mesh;
            out->ImportFile(file);
            return out;
        }

        RL_LOG_ERROR("Unable to import file. Unknown file type: ", ext);
        return nullptr;
    }

    std::shared_ptr<AssetData> AssetData::OpenAssetFile(const std::filesystem::path& file)
    {
        std::ifstream input;
        input.open(file, std::ios::binary);
        if (!input.is_open())
        {
            RL_LOG_ERROR("unable to open file");
            return nullptr;
        }

        std::string code = "";
        input.read(code.data(), 2);
        if(code != "RL")
        {
            RL_LOG_ERROR("Corrupted asset file, unable to read: ", code);
        }

        AssetType type;
        input.read((char*)&type, sizeof(type));

        RL_LOG_WARNING("Type: ", AssetTypeToString(type));
        return nullptr;
    }

    void AssetData::Save()
    {
        std::ofstream output;
        output.open(file, std::ios::binary);
        if (!output.is_open())
        {
            RL_LOG_ERROR("unable to open file");
            return;
        }

        output << "RL";
        output << std::bit_cast<char>(type);

        WriteData(output);

        output.close();
    }

    void AssetData::CheckForUpdates(const std::filesystem::path& file) {}
}