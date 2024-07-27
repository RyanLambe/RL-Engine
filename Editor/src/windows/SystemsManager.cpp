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
            if (!ProjectManager::IsProjectOpen())
            {
                ImGui::Text("No project is currently open.");
                ImGui::End();
                return;
            }
            if (!ProjectManager::IsProjectCompiled())
            {
                ImGui::Text("The project has not been compiled yet.");
                ImGui::End();
                return;
            }

            bool disabled = Editor::Playing();
            float SystemHeight = Editor::GetFontSize() * 2;
            ImVec2 nextItemPos;
            ImVec2 ChildSize;
            bool popColor;
            bool exitForLoop = false;

            if (disabled)
                ImGui::BeginDisabled();

            for (int i = 0; i < systems.size(); i++)
            {
                nextItemPos = ImVec2(ImGui::GetWindowPos().x + ImGui::GetCursorPos().x,
                                     ImGui::GetWindowPos().y + ImGui::GetCursorPos().y);
                ChildSize
                    = ImVec2(ImGui::GetContentRegionAvail().x, SystemHeight + ImGui::GetStyle().ItemSpacing.y * 4);
                popColor = false;

                if (!disabled
                    && ImGui::IsMouseHoveringRect(nextItemPos,
                                                  ImVec2(nextItemPos.x + ChildSize.x, nextItemPos.y + ChildSize.y)))
                {
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_TextSelectedBg));
                    popColor = true;
                }

                if (ImGui::BeginChild(("sys" + std::to_string(i)).c_str(), ChildSize, ImGuiChildFlags_Border))
                {
                    // check box
                    float temp = ImGui::GetCursorPosY();
                    ImGui::SetCursorPosY(temp + (SystemHeight / 2) - (ImGui::GetFrameHeight() / 2));
                    if (ImGui::Checkbox(("##Box" + std::to_string(i)).c_str(), &systems[i].first))
                    {
                        UpdateSystems();
                    }

                    // text
                    ImGui::SameLine();
                    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(systems[i].second.c_str()).x)
                                         / 2);
                    ImGui::Text("%s", systems[i].second.c_str());
                    ImGui::SameLine();

                    // delete button
                    ImGui::SetCursorPosY(temp);
                    ImGui::SetCursorPosX(ImGui::GetWindowSize().x - SystemHeight - ImGui::GetStyle().ItemSpacing.y * 2);

                    ImGui::PushFont(Editor::GetWingdingFont());
                    if (ImGui::Button(("T##" + std::to_string(i)).c_str(), ImVec2(SystemHeight, SystemHeight)))
                    {
                        systems.erase(systems.begin() + i);
                        UpdateSystems();
                        exitForLoop = true;
                    }
                    ImGui::PopFont();
                }

                if (!exitForLoop && !disabled)
                {
                    if (TryMoveSystem(i))
                        exitForLoop = true;
                }

                ImGui::EndChild();
                if (popColor)
                    ImGui::PopStyleColor();
                if (exitForLoop)
                    break;
            }

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
            if (ImGui::Button("Add System", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                ImGui::OpenPopup("Add System Menu");
            DrawAddSystemMenu();

            if (disabled)
                ImGui::EndDisabled();

            if (ImGui::IsMouseReleased(0))
            {
                moving = -1;
            }
        }
        ImGui::End();
    }

    bool SystemsManager::IsOpen()
    {
        return open;
    }

    bool SystemsManager::TryMoveSystem(int systemIndex)
    {
        if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(0) && moving == -1)
        {
            moving = systemIndex;
        }

        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem) && moving == systemIndex)
            hoveredMoving = true;

        if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem) && moving == systemIndex
            && hoveredMoving)
        {
            int swapIndex = systemIndex + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
            if (swapIndex >= 0 && swapIndex < systems.size())
            {
                auto temp = systems[systemIndex];
                systems[systemIndex] = systems[swapIndex];
                systems[swapIndex] = temp;

                moving = swapIndex;
                hoveredMoving = false;

                ImGui::ResetMouseDragDelta();
                return true;
            }
        }
        return false;
    }

    void SystemsManager::DrawAddSystemMenu()
    {
        if (ImGui::BeginPopup("Add System Menu"))
        {
            ImGui::Text("Add System:\t\t\t\t\t");
            ImGui::Separator();

            for (const auto& system : CodeManager::GetSystems())
            {
                if (ImGui::Button(Editor::FormatName(system).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                {
                    systems.emplace_back(true, system);
                    UpdateSystems();

                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
    }

    void SystemsManager::UpdateSystems()
    {
        Application::GetScene().systemManager.RemoveAllSystems();
        for (const auto& system : systems)
        {
            if (!system.first)
                continue;

            CodeManager::AddSystem(system.second);
        }
    }
}