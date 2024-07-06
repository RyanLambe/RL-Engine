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
            }
            ImGui::SameLine();

            ImFont font = *ImGui::GetFont();
            font.Scale *= 1.2;
            ImGui::PushFont(&font);
            ImGui::Text("%s", currPath.filename().string().c_str());
            ImGui::PopFont();

            const float padding = ImGui::GetStyle().ItemInnerSpacing.x;
            const float outerPadding = ImGui::GetStyle().ItemSpacing.x;
            const float area = ImGui::GetCurrentWindow()->InnerRect.GetWidth() - outerPadding * 2;
            const int columns = max(std::floor(area / (iconSize + padding * 2)), 1.0f);
            int i = 0;

            ImGui::SetCursorPosX((outerPadding + area - ((iconSize + padding * 2) * (float)columns)) / 2);

            if (ImGui::BeginChild("files")) {
                for (const auto & entry : std::filesystem::directory_iterator(currPath)){

                    ImGui::PushID(i);
                    ImGui::BeginGroup();
                    if(entry.is_directory()){
                        if(ImGui::Button("Dir", ImVec2(iconSize, iconSize))) {
                            RL_LOG(entry.path().string());
                            currPath = entry.path();
                        }
                    }
                    else {
                        if(ImGui::Button("File", ImVec2(iconSize, iconSize))) {

                        }
                    }

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
}