#include "SceneHierarchy.h"

#include "../Editor.h"
#include "Components.h"

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
        if (ImGui::Begin("Scene Hierarchy", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse))
        {
            if (ImGui::Button("New Folder"))
            {
                hierarchy.emplace_back(ElementType::Folder, nextFolder, "Folder " + std::to_string(nextFolder));
                hierarchy.emplace_back(ElementType::FolderEnd, nextFolder, "Folder " + std::to_string(nextFolder));
                nextFolder++;
            }
            ImGui::SameLine();
            if (ImGui::Button("New Entity"))
            {
                Entity entity = Application::GetScene().CreateEntity();
                hierarchy.emplace_back(ElementType::Entity, entity, "Entity " + std::to_string(entity));
            }

            DrawHierarchy();

            if (ImGui::IsMouseReleased(0))
            {
                moving = "";
            }
        }
        ImGui::End();
    }

    bool SceneHierarchy::IsOpen()
    {
        return open;
    }

    void SceneHierarchy::SetEntityName(rl::Entity entity, const std::string& name)
    {
        for (auto& element : window->hierarchy)
        {
            if (element.type == ElementType::Entity && element.id == entity)
                element.name = name.empty() ? "Entity " + std::to_string(entity) : name;
        }
    }

    void SceneHierarchy::DrawHierarchy()
    {
        std::vector<bool> treeVisibleStack;
        treeVisibleStack.push_back(true);
        float cursorPos = ImGui::GetCursorPosX();

        for (int i = 0; i < hierarchy.size(); i++)
        {
            switch (hierarchy[i].type)
            {
                case ElementType::Entity:
                    if (treeVisibleStack.back())
                    {
                        ImGui::SetCursorPosX(cursorPos);
                        if (ImGui::Selectable((hierarchy[i].name + "##e" + std::to_string(hierarchy[i].id)).c_str()))
                        {
                            Components::SelectEntity(hierarchy[i].id, hierarchy[i].name);
                        }
                    }
                    break;

                case ElementType::Folder:
                    if (treeVisibleStack.back())
                    {
                        ImGui::SetCursorPosX(cursorPos);
                        if (ImGui::Selectable((hierarchy[i].name + "##f" + std::to_string(hierarchy[i].id)).c_str()))
                        {
                            hierarchy[i].enabled = !hierarchy[i].enabled;
                        }
                        treeVisibleStack.push_back(hierarchy[i].enabled);
                    }
                    else
                        treeVisibleStack.push_back(false);
                    cursorPos += 16;
                    break;

                case ElementType::FolderEnd:
                    if (treeVisibleStack.back())
                    {
                        ImGui::SetCursorPosX(cursorPos);
                        ImGui::Separator();
                    }
                    hierarchy[i].enabled = treeVisibleStack.back();
                    treeVisibleStack.pop_back();
                    cursorPos -= 16;
                    continue;
            }
            if (hierarchy[i].type == ElementType::FolderEnd)
                continue;

            // handle input

            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) && ImGui::IsMouseClicked(1))
            {
                ImGui::OpenPopup(
                        ("popup" + std::to_string((uint8_t)hierarchy[i].type) + std::to_string(hierarchy[i].id)).c_str());
                rightClickedElement = i;
                rightClickedEnabled = true;
            }
            if (i == rightClickedElement && ImGui::IsMouseClicked(1)
                && !ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
            {
                rightClickedEnabled = false;
            }
            if (DrawRightClickMenu(hierarchy[i].type, i))
                break;

            if (ImGui::IsMouseDown(0) && ImGui::IsItemHovered() && moving.empty())
            {
                moving = hierarchy[i].name;
            }

            if (TryMoveElement(i))
                break;
        }
    }

    int SceneHierarchy::GetHierarchyElementSize(int element) const
    {
        int size = 1;

        if (hierarchy[element].type == ElementType::Folder)
        {
            int subLevel = 1;
            for (int j = element + 1; j < hierarchy.size(); j++)
            {
                if (hierarchy[j].type == ElementType::Folder)
                    subLevel++;
                else if (hierarchy[j].type == ElementType::FolderEnd)
                    subLevel--;
                size++;

                if (subLevel <= 0)
                    break;
            }
        }

        return size;
    }

    bool SceneHierarchy::TryMoveElement(int elementIndex)
    {
        if (hierarchy[elementIndex].name == moving && !ImGui::IsItemHovered())
        {
            int size = GetHierarchyElementSize(elementIndex);
            int dest = elementIndex + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
            if (dest >= 0 && dest + size <= hierarchy.size() && hierarchy.size() > 1)
            {
                if (hierarchy[elementIndex].name != hierarchy[dest].name && hierarchy[dest].type == ElementType::Folder
                    && !hierarchy[dest].enabled)
                {
                    dest += GetHierarchyElementSize(dest) - 1;
                }
                else if (hierarchy[elementIndex].name != hierarchy[dest].name
                         && hierarchy[dest].type == ElementType::FolderEnd && !hierarchy[dest].enabled)
                {
                    dest -= GetHierarchyElementSize(dest) + 1;
                }
                dest = std::max(dest, 0);

                std::vector<Element> temp = {};
                temp.insert(temp.begin(), hierarchy.begin() + elementIndex, hierarchy.begin() + elementIndex + size);
                hierarchy.erase(hierarchy.begin() + elementIndex, hierarchy.begin() + elementIndex + size);
                hierarchy.insert(hierarchy.begin() + dest, temp.begin(), temp.end());

                ImGui::ResetMouseDragDelta();
                return true;
            }
        }
        return false;
    }

    bool SceneHierarchy::DrawRightClickMenu(ElementType type, int index)
    {
        if (!rightClickedEnabled || index != rightClickedElement)
            return false;

        if (ImGui::BeginPopupContextWindow(
                ("popup" + std::to_string((uint8_t)hierarchy[index].type) + std::to_string(hierarchy[index].id))
                    .c_str()))
        {
            ImGui::Text("%s", hierarchy[index].name.c_str());
            ImGui::Separator();

            if (ImGui::Button("Delete"))
            {
                size_t idToDel = hierarchy[index].id;
                std::vector<Element>::iterator iter;
                for (iter = hierarchy.begin(); iter != hierarchy.end();)
                {
                    if (iter->id == idToDel
                        && (iter->type == type
                            || (type == ElementType::Folder && iter->type == ElementType::FolderEnd)))
                        iter = hierarchy.erase(iter);
                    else
                        ++iter;
                }
                if (type == ElementType::Folder)
                    deletedFolders.emplace_back(idToDel);
                if (type == ElementType::Entity)
                    Application::GetScene().DestroyEntity(idToDel);

                rightClickedEnabled = false;
                ImGui::EndPopup();
                return true;
            }
            ImGui::EndPopup();
        }
        return false;
    }
}
