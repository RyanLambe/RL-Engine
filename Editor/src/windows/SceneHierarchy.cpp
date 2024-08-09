#include "SceneHierarchy.h"

#include <fstream>
#include <ranges>

#include "../Editor.h"
#include "../project/ProjectManager.h"

namespace rl::ed
{
    std::shared_ptr<SceneHierarchy> SceneHierarchy::window = nullptr;

    void SceneHierarchy::OpenWindow()
    {
        if (!window)
        {
            window = std::make_shared<SceneHierarchy>();
        }
        window->open = true;
        Editor::AddGuiElement(window);
    }

    void SceneHierarchy::CloseWindow()
    {
        window->open = false;
    }

    void SceneHierarchy::Render()
    {
        if (ImGui::Begin("Scene Hierarchy", &open, ImGuiWindowFlags_NoCollapse))
        {
            if (!ProjectManager::IsProjectOpen())
            {
                ImGui::Text("No project is currently open.");
                ImGui::End();
                return;
            }

            try{
                Application::GetSceneManager().GetCurrentScene();
            }
            catch(...){
                ImGui::Text("No scene is currently open.");
                ImGui::End();
                return;
            }

            std::vector<Entity> stack;
            stack.push_back(0);

            while (!stack.empty())
            {
                Entity entity = stack.back();
                stack.pop_back();
                for (const auto& child : Scene::GetScene().GetChildren(entity) | std::views::reverse)
                {
                    stack.push_back(child);
                }

                if (entity != NullEntity)
                {
                    DrawSeparator(entity);
                    DrawEntity(entity);
                }

                if (entity == NullEntity)
                {
                    ImGui::Text("\t%s", Scene::GetScene().GetEntityData(NullEntity)->name.c_str());
                    ImGui::Separator();
                }
            }

            if (ImGui::IsWindowHovered() && selected != NullEntity
                && (ImGui::IsMouseClicked(0) || ImGui::IsMouseClicked(1)))
            {
                selected = NullEntity;
            }

            if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_ChildWindows)
                && ImGui::IsMouseClicked(1))
            {
                ImGui::OpenPopup("Hierarchy Right Click Menu");
            }
            DrawRightClickMenu();

            if (ImGui::IsMouseReleased(0) && moving != NullEntity)
            {
                if (ImGui::IsWindowHovered())
                {
                    Scene::GetScene().SetParent(NullEntity, moving);
                }
                moving = NullEntity;
            }
        }
        ImGui::End();

        if (moving != NullEntity)
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_::ImGuiMouseCursor_Hand);
        }
        else
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_::ImGuiMouseCursor_Arrow);
        }
    }

    bool SceneHierarchy::IsOpen()
    {
        return open;
    }

    Entity SceneHierarchy::GetSelected()
    {
        return window->selected;
    }

    void SceneHierarchy::DrawEntity(Entity entity)
    {
        // check if hovered
        ImVec2 nextItemPos = ImVec2(ImGui::GetWindowPos().x + ImGui::GetCursorPos().x,
                                    ImGui::GetWindowPos().y + ImGui::GetCursorPos().y + hoverRectOffset);
        ImVec2 ChildSize = ImVec2(ImGui::GetContentRegionAvail().x, Editor::GetFontSize() - hoverRectOffset * 2);
        nextHoverRectPos = ImVec2(nextItemPos.x, nextItemPos.y + ChildSize.y + 1);
        bool hovered = !popupOpen
                       && ImGui::IsMouseHoveringRect(nextItemPos,
                                                     ImVec2(nextItemPos.x + ChildSize.x, nextItemPos.y + ChildSize.y));

        bool shouldPopWindowColor = false;
        if (selected == entity || moving == entity || hovered)
        {
            if (entity != NullEntity)
            {
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_TextSelectedBg));
                shouldPopWindowColor = true;
            }
        }

        ImGui::SetCursorPosX(Editor::GetFontSize() * GetEntityDepth(entity));
        if (ImGui::BeginChild(("e:" + std::to_string(entity)).c_str(), ImVec2(0, 0), ImGuiChildFlags_AutoResizeY))
        {
            ImGui::PushFont(Editor::GetWingdingFont());
            ImGui::Text("a");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::Text("%s", Scene::GetScene().GetEntityData(entity)->name.c_str());

            if (ImGui::IsMouseClicked(1) && hovered && moving == NullEntity)
            {
                selected = entity;
            }

            if (ImGui::IsMouseClicked(0) && hovered && moving == NullEntity)
            {
                selected = entity;
                moving = entity;
            }

            if (ImGui::IsMouseReleased(0) && hovered && moving != NullEntity && moving != entity)
            {
                Scene::GetScene().SetParent(entity, moving);
                moving = NullEntity;
            }
            else if (ImGui::IsMouseReleased(0) && hovered && moving != NullEntity)
            {
                moving = NullEntity;
            }
        }
        ImGui::EndChild();

        if (shouldPopWindowColor)
            ImGui::PopStyleColor();
    }

    void SceneHierarchy::DrawSeparator(Entity entity)
    {
        ImVec2 ChildSize = ImVec2(ImGui::GetContentRegionAvail().x,
                                  (ImGui::GetStyle().ItemSpacing.y * 2) + (hoverRectOffset * 2) - 2);
        bool hovered = !popupOpen
                       && ImGui::IsMouseHoveringRect(nextHoverRectPos, ImVec2(nextHoverRectPos.x + ChildSize.x,
                                                                              nextHoverRectPos.y + ChildSize.y));

        if (hovered && moving != NullEntity)
        {
            ImGui::PushStyleColor(ImGuiCol_Separator, ImGui::GetStyleColorVec4(ImGuiCol_FrameBgActive));
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Separator, ImGui::GetStyleColorVec4(ImGuiCol_ChildBg));
        }

        ImGui::SetCursorPosX(Editor::GetFontSize() * GetEntityDepth(entity));
        ImGui::Separator();

        if (ImGui::IsMouseReleased(0) && hovered && moving != NullEntity && moving != entity)
        {
            Scene::GetScene().SetParent(Scene::GetScene().GetParent(entity), moving);
            Scene::EntityData* data = Scene::GetScene().GetEntityData(Scene::GetScene().GetParent(entity));
            for (int i = data->children.size() - 1; i >= 0; i--)
            {
                if (data->children[i] == moving)
                {
                    data->children.erase(data->children.begin() + i);
                    i--;
                }
                if (data->children[i] == entity)
                {
                    data->children.insert(data->children.begin() + i, moving);
                }
            }
            moving = NullEntity;
        }
        else if (ImGui::IsMouseReleased(0) && hovered && moving != NullEntity)
        {
            moving = NullEntity;
        }

        ImGui::PopStyleColor();
    }

    void SceneHierarchy::DrawRightClickMenu()
    {
        if (ImGui::BeginPopupContextWindow("Hierarchy Right Click Menu"))
        {
            if (selected == NullEntity)
            {
                if (ImGui::Button("Create Entity"))
                {
                    Scene::GetScene().CreateEntity();
                    ImGui::CloseCurrentPopup();
                }
            }
            else
            {
                auto selectedData = Scene::GetScene().GetEntityData(selected);
                if (!selectedData)
                {
                    ImGui::Text("Unable to find entity: %zu", selected);
                    ImGui::EndPopup();
                    return;
                }

                ImGui::Text("%s\t\t\t", selectedData->name.c_str());
                ImGui::Separator();

                if (ImGui::Button("Create Entity"))
                {
                    Entity child = Scene::GetScene().CreateEntity();
                    Scene::GetScene().SetParent(selected, child);

                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::Button("Delete"))
                {
                    Scene::GetScene().DestroyEntity(selected);
                    selected = NullEntity;
                    moving = NullEntity;

                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
            popupOpen = true;
        }
        else
        {
            popupOpen = false;
        }
    }

    float SceneHierarchy::GetEntityDepth(Entity entity)
    {
        if (entity == NullEntity)
            return 0;
        return GetEntityDepth(Scene::GetScene().GetParent(entity)) + 1.0f;
    }
}
