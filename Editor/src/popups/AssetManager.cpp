#include "AssetManager.h"

#include "../Editor.h"

namespace rl::ed {

    std::shared_ptr<AssetManager> AssetManager::popup = nullptr;

    void AssetManager::OpenNewAssetPopup(const std::filesystem::path& location) {
        if (!popup || (popup && popup->IsOpen() && popup->importAsset))
        {
            popup = std::make_shared<AssetManager>();
        }
        popup->open = true;
        Editor::AddGuiElement(popup);

        popup->importAsset = false;
        popup->location = location;
    }

    void AssetManager::OpenImportAssetPopup(const std::filesystem::path& file) {
        if (!popup || (popup && popup->IsOpen() && !popup->importAsset))
        {
            popup = std::make_shared<AssetManager>();
        }
        popup->open = true;
        Editor::AddGuiElement(popup);

        popup->importAsset = true;
        popup->location = file.parent_path();
        file.filename().string().copy((char*)popup->filenameBuf, 256);
    }

    void AssetManager::ClosePopup() {
        popup->open = false;
    }

    void AssetManager::Render() {
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::Begin(importAsset ? "Import Asset" : "New Asset", &open, ImGuiWindowFlags_NoDocking))
        {
            ImGui::SetWindowSize(ImVec2(600, 300));

            if(importAsset){
                ImGui::Text("Asset Name: %s", (char*)filenameBuf);
            }
            else{
                ImGui::Text("Asset Name: ");
                ImGui::SameLine();
                ImGui::InputText("##name", (char*)filenameBuf, 256);
            }

            ImGui::Text("File Type: ");
            ImGui::SameLine();

            class Test{
            public:
                Test(int n) : n(n) {}
                int n;
                [[nodiscard]] std::string GetFormatName() const {
                    return "test " + std::to_string(n);
                }
            };

            std::vector<Test> tests;
            tests.emplace_back(1);
            tests.emplace_back(2);
            tests.emplace_back(3);
            tests.emplace_back(4);
            tests.emplace_back(5);

            std::string list;
            for(const auto& test : tests){
                list += test.GetFormatName() + '\0';
            }


            static int currItem = 0;
            ImGui::Combo("##fileType", &currItem, list.c_str());

            if(ImGui::Button(importAsset ? "Import" : "Create")){

            }

            ImGui::End();
        }
    }

    bool AssetManager::IsOpen() {
        return open;
    }

}