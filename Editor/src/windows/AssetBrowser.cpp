#include "AssetBrowser.h"

#include "../Editor.h"
#include "../project/ProjectManager.h"

#include "imgui_internal.h"

namespace rl::ed {
    std::shared_ptr<AssetBrowser> AssetBrowser::window = nullptr;

    void AssetBrowser::OpenWindow()
    {
        if (!window)
        {
            window = std::make_shared<AssetBrowser>();
        }
        window->open = true;
        Editor::AddGuiElement(window);
    }

    void AssetBrowser::CloseWindow()
    {
        window->open = false;
    }

    void AssetBrowser::Render() {
        if (ImGui::Begin("Asset Browser", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse))
        {
            if(!ProjectManager::IsProjectOpen()){
                ImGui::Text("No project is open.");
                return;
            }

            ImGui::Button("New");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(250);
            ImGui::SliderFloat("Icon Size", &iconSize, 25, 250);

            if(ImGui::Button("Back") && currPath != rootPath){
                currPath = currPath.parent_path();
                selectedFile = std::nullopt;
            }
            ImGui::SameLine();

            ImFont font = *ImGui::GetFont();
            font.Scale *= 1.2;
            ImGui::PushFont(&font);
            ImGui::Text("%s", currPath.filename().string().c_str());
            ImGui::PopFont();

            // draw files
            const float padding = ImGui::GetStyle().ItemInnerSpacing.x;
            const float outerPadding = ImGui::GetStyle().ItemSpacing.x;
            const float area = ImGui::GetCurrentWindow()->InnerRect.GetWidth() - outerPadding * 2;
            const int columns = max(std::floor(area / (iconSize + padding * 2)), 1.0f);
            int i = 0;

            ImGui::SetCursorPosX((outerPadding + area - ((iconSize + padding * 2) * (float)columns)) / 2);
            newFileSelected = false;

            if (ImGui::BeginChild("files")) {
                for (const auto& entry : std::filesystem::directory_iterator(currPath)){

                    ImGui::PushID(i);
                    ImGui::BeginGroup();

                    DrawFileButton(entry);

                    // get text
                    std::string text = entry.path().filename().string();
                    if(text.length() >= 75)
                        text = text.substr(0, 75 - 3) + "...";

                    // write text
                    ImGui::PushTextWrapPos(((float)(i % columns) * (iconSize + padding * 2)) + iconSize);
                    ImGui::TextWrapped("%s", text.c_str());
                    ImGui::PopTextWrapPos();

                    ImGui::EndGroup();
                    ImGui::PopID();

                    i++;
                    if(i % columns != 0)
                        ImGui::SameLine();
                }
                ImGui::EndChild();

                if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) && ImGui::IsMouseClicked(1))
                    ImGui::OpenPopup("popup");
                DrawRightClickMenu();

                if((ImGui::IsMouseClicked(0) || ImGui::IsMouseClicked(1)) && !(newFileSelected || ImGui::IsPopupOpen("popup"))) {
                    selectedFile = std::nullopt;
                }
            }
            ImGui::End();
        }
    }

    bool AssetBrowser::IsOpen() {
        return open;
    }

    void AssetBrowser::Setup(const std::string &projectDir) {
        window->rootPath = projectDir + "/Assets";
        window->currPath = projectDir + "/Assets";
    }

    void AssetBrowser::DrawFileButton(const std::filesystem::directory_entry& entry) {

        // draw
        if(entry == selectedFile)
            ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0,255,0,255));
        ImGui::Button(entry.is_directory() ? "Dir" : "File", ImVec2(iconSize, iconSize));
        if(entry == selectedFile)
            ImGui::PopStyleColor();

        // select
        if(ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) && (ImGui::IsMouseClicked(0) || ImGui::IsMouseClicked(1))){
            selectedFile = entry;
            newFileSelected = true;
        }

        // open
        if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
            if(entry.is_directory()){
                currPath = entry.path();
                selectedFile = std::nullopt;
            }
            else{
                RL_LOG(entry.path().string());
                system(("explorer \"" + entry.path().parent_path().string() + "\"").c_str());
            }
        }
    }

    void AssetBrowser::DrawRightClickMenu() const {

        if(ImGui::BeginPopupContextWindow("popup")){

            if(ImGui::Button("New")){
                // ???
            }

            if(selectedFile.has_value()){
                ImGui::Separator();
                if(ImGui::Button("Delete")){
                    std::filesystem::remove(selectedFile->path());
                }
                if(ImGui::Button("Rename")){
                    // ???
                }
            }

            ImGui::EndPopup();
        }
    }
}