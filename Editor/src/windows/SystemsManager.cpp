#include "SystemsManager.h"

#include "../Editor.h"
#include "../tools/CodeManager.h"

namespace rl::ed
{

    std::shared_ptr<SystemsManager> SystemsManager::window = nullptr;

    void SystemsManager::OpenWindow()
    {
        if (!window)
        {
            window = std::make_shared<SystemsManager>();
        }
        window->open = true;
        Editor::AddGuiElement(window);
    }

    void SystemsManager::CloseWindow()
    {
        window->open = false;
    }

    void SystemsManager::Render()
    {
        if (ImGui::Begin("Systems Manager", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse))
        {
            float SystemHeight = Editor::GetFontSize() * 2;
            ImVec2 nextItemPos;
            ImVec2 ChildSize;
            bool popColor;

            for (int i = 0; i < CodeManager::GetSystems().size(); i++)
            {
                nextItemPos = ImVec2(ImGui::GetWindowPos().x + ImGui::GetCursorPos().x,
                                     ImGui::GetWindowPos().y + ImGui::GetCursorPos().y);
                ChildSize
                    = ImVec2(ImGui::GetContentRegionAvail().x, SystemHeight + ImGui::GetStyle().ItemSpacing.y * 4);
                popColor = false;

                if (ImGui::IsMouseHoveringRect(nextItemPos,
                                               ImVec2(nextItemPos.x + ChildSize.x, nextItemPos.y + ChildSize.y)))
                {
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_TextSelectedBg));
                    popColor = true;
                }

                if (ImGui::BeginChild(("sys" + CodeManager::GetSystems()[i]).c_str(), ChildSize,
                                      ImGuiChildFlags_Border))
                {
                    // check box
                    static bool t = false;
                    float temp = ImGui::GetCursorPosY();
                    ImGui::SetCursorPosY(temp + (SystemHeight / 2) - (ImGui::GetFrameHeight() / 2));
                    ImGui::Checkbox(("##Box" + CodeManager::GetSystems()[i]).c_str(), &t);

                    // text
                    ImGui::SameLine();
                    ImGui::SetCursorPosX(
                        (ImGui::GetWindowSize().x - ImGui::CalcTextSize(CodeManager::GetSystems()[i].c_str()).x) / 2);
                    ImGui::Text("%s", CodeManager::GetSystems()[i].c_str());
                    ImGui::SameLine();

                    // delete button
                    ImGui::SetCursorPosY(temp);
                    ImGui::SetCursorPosX(ImGui::GetWindowSize().x - SystemHeight - ImGui::GetStyle().ItemSpacing.y * 2);

                    ImGui::PushFont(Editor::GetWingdingFont());
                    ImGui::Button(("T##" + CodeManager::GetSystems()[i]).c_str(), ImVec2(SystemHeight, SystemHeight));
                    ImGui::PopFont();
                }
                ImGui::EndChild();
                if (popColor)
                    ImGui::PopStyleColor();
            }

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
            if (ImGui::Button("Add System", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                ImGui::OpenPopup("Add System Menu");
            DrawAddSystemMenu();
        }
        ImGui::End();
    }

    bool SystemsManager::IsOpen()
    {
        return open;
    }

    void SystemsManager::DrawAddSystemMenu() {
        if (ImGui::BeginPopup("Add System Menu"))
        {
            ImGui::Text("Add System:\t\t\t\t\t");
            ImGui::Separator();

            for (const auto& system : CodeManager::GetSystems())
            {
                if (ImGui::Button(Editor::FormatName(system).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                {

                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
    }
}