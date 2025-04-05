#include "AssetManager.h"

#include "../Editor.h"
#include "../tools/CodeManager.h"

namespace rl::ed
{

    std::shared_ptr<AssetManager> AssetManager::popup = nullptr;

    void AssetManager::OpenNewAssetPopup(const std::filesystem::path& location)
    {
        if (!popup || (popup && popup->IsOpen() && popup->importAsset))
        {
            popup = std::make_shared<AssetManager>();
        }
        popup->open = true;
        Editor::AddGuiElement(popup);

        popup->importAsset = false;
        popup->location = location;
        popup->filenameBuf[0] = '\0';
    }

    void AssetManager::OpenImportAssetPopup(const std::filesystem::path& file)
    {
        if (!popup || (popup && popup->IsOpen() && !popup->importAsset))
        {
            popup = std::make_shared<AssetManager>();
        }
        popup->open = true;
        Editor::AddGuiElement(popup);

        popup->importAsset = true;
        popup->location = file.parent_path();
        popup->filenameBuf[0] = '\0';
        file.filename().string().copy((char*)popup->filenameBuf, 256);
    }

    void AssetManager::ClosePopup()
    {
        popup->open = false;
    }

    void AssetManager::Render()
    {
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::Begin(importAsset ? "Import Asset" : "New Asset", &open, ImGuiWindowFlags_NoDocking))
        {
            ImGui::SetWindowSize(ImVec2(600, 300));

            if (importAsset)
            {
                ImGui::Text("Asset Name: %s", (char*)filenameBuf);
            }
            else
            {
                ImGui::Text("Asset Name: ");
                ImGui::SameLine();
                ImGui::InputText("##name", (char*)filenameBuf, 256);
            }

            ImGui::Text("File Type: ");
            ImGui::SameLine();

            std::vector<AssetType> types;
            if(importAsset)
            {
                types.push_back(AssetType::Mesh);
            }
            else
            {
                types.push_back(AssetType::Folder);
                types.push_back(AssetType::Scene);
                types.push_back(AssetType::System);
                types.push_back(AssetType::Component);
            }

            std::string list;
            for (const auto& type : types)
            {
                list += AssetTypeToString(type) + '\0';
            }

            static int currItem = 0;
            ImGui::Combo("##fileType", &currItem, list.c_str());

            if(importAsset)
            {
                if(ImGui::Button("Import"))
                {
                    Application::GetAssetManager().ImportFromFile(location);
                    ClosePopup();
                }
            }
            else
            {
                if(ImGui::Button("Create"))
                {
                    Application::GetAssetManager().CreateAsset(location, std::string(filenameBuf), types[currItem]);
                    if (types[currItem] == AssetType::Component) {
                        size_t pos = location.string().find("Assets");
                        std::string tempPath = location.string().substr(pos) + "/" + std::string(filenameBuf);
                        std::replace(tempPath.begin(), tempPath.end(), '\\', '/');
                        CodeManager::AddComponent(tempPath + ".cpp", tempPath + ".h");
                    }

                    if (types[currItem] == AssetType::System) {
                        size_t pos = location.string().find("Assets");
                        std::string tempPath = location.string().substr(pos) + "/" + std::string(filenameBuf);
                        std::replace(tempPath.begin(), tempPath.end(), '\\', '/');
                        CodeManager::AddSystem(tempPath + ".cpp", tempPath + ".h");
                    }
                    ClosePopup();
                }
            }

            ImGui::End();
        }
    }

    bool AssetManager::IsOpen()
    {
        return open;
    }

}
