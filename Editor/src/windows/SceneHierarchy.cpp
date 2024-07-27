#include "SceneHierarchy.h"

#include <algorithm>

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
        if (ImGui::Begin("Scene Hierarchy", &open, ImGuiWindowFlags_NoCollapse))
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

            if (ImGui::Button("New Entity", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0.0f)))
            {
                Entity entity = Application::GetScene().CreateEntity();
                hierarchy.emplace_back(ElementType::Entity, entity, "Entity " + std::to_string(entity));
            }
            ImGui::SameLine();
            if (ImGui::Button("New Folder", ImVec2(ImGui::GetContentRegionAvail().x, 0.0f)))
            {
                size_t idToUse;
                if (deletedFolders.empty())
                {
                    idToUse = nextFolder;
                    nextFolder++;
                }
                else
                {
                    idToUse = deletedFolders.front();
                    deletedFolders.pop();
                }
                hierarchy.emplace_back(ElementType::Folder, idToUse, "Folder " + std::to_string(idToUse));
                hierarchy.emplace_back(ElementType::FolderEnd, idToUse, "Folder " + std::to_string(idToUse));
            }

            DrawHierarchy();

            if (ImGui::IsMouseReleased(0))
            {
                moving.clear();
                moved = false;
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

    void SceneHierarchy::SetFolderName(size_t folder, const std::string& name)
    {
        for (auto& element : window->hierarchy)
        {
            if ((element.type == ElementType::Folder || element.type == ElementType::FolderEnd) && element.id == folder)
                element.name = name.empty() ? "Folder " + std::to_string(folder) : name;
        }
    }

    void SceneHierarchy::DrawHierarchy()
    {
        std::vector<bool> treeVisibleStack;
        treeVisibleStack.push_back(true);
        float cursorPos = ImGui::GetCursorPosX();
        bool shouldCloseChildWindow;
        bool shouldPopWindowColor;

        for (int i = 0; i < hierarchy.size(); i++)
        {
            shouldCloseChildWindow = false;
            shouldPopWindowColor = false;
            switch (hierarchy[i].type)
            {
                case ElementType::Entity:
                    if (treeVisibleStack.back())
                    {
                        if (Components::IsSelected(hierarchy[i].id, false))
                        {
                            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_TextSelectedBg));
                            shouldPopWindowColor = true;
                        }

                        if (ImGui::BeginChild(('e' + std::to_string(hierarchy[i].id)).c_str(), ImVec2(0, 0),
                                              ImGuiChildFlags_AutoResizeY))
                        {
                            ImGui::SetCursorPosX(cursorPos);
                            ImGui::PushFont(Editor::GetWingdingFont());
                            ImGui::Text("a");
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::Text("%s", hierarchy[i].name.c_str());

                            if (ImGui::IsMouseReleased(0) && ImGui::IsWindowHovered() && !moved)
                            {
                                Components::SelectEntity(hierarchy[i].id, hierarchy[i].name);
                            }
                        }
                        shouldCloseChildWindow = true;
                    }
                    break;

                case ElementType::Folder:
                    if (treeVisibleStack.back())
                    {
                        if (Components::IsSelected(hierarchy[i].id, true))
                        {
                            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_TextSelectedBg));
                            shouldPopWindowColor = true;
                        }

                        if (ImGui::BeginChild(('f' + std::to_string(hierarchy[i].id)).c_str(), ImVec2(0, 0),
                                              ImGuiChildFlags_AutoResizeY))
                        {
                            ImGui::SetCursorPosX(cursorPos);
                            ImGui::PushFont(Editor::GetWingdingFont());
                            std::string symbols;
                            if (hierarchy[i].enabled)
                                symbols += 'e';
                            else
                                symbols += 'd';
                            if (hierarchy[i + 1].type == ElementType::FolderEnd)
                                symbols += 'c';
                            else
                                symbols += 'b';
                            ImGui::Text("%s", symbols.c_str());
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::Text("%s", hierarchy[i].name.c_str());
                        }
                        shouldCloseChildWindow = true;
                        if (ImGui::IsMouseReleased(0) && ImGui::IsWindowHovered() && !moved)
                        {
                            Components::SelectFolder(hierarchy[i].id, hierarchy[i].name);
                            hierarchy[i].enabled = !hierarchy[i].enabled;
                        }
                        treeVisibleStack.push_back(hierarchy[i].enabled);
                    }
                    else
                        treeVisibleStack.push_back(false);
                    cursorPos += Editor::GetFontSize() * 1.25f;
                    break;

                case ElementType::FolderEnd:
                    hierarchy[i].enabled = treeVisibleStack.back();
                    treeVisibleStack.pop_back();
                    cursorPos -= Editor::GetFontSize() * 1.25f;
                    continue;
            }

            // handle input

            if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) && ImGui::IsMouseClicked(1))
            {
                ImGui::OpenPopup(
                    ("popup" + std::to_string((uint8_t)hierarchy[i].type) + std::to_string(hierarchy[i].id)).c_str());
                rightClickedElement = i;
                rightClickedEnabled = true;
            }
            if (i == rightClickedElement && ImGui::IsMouseClicked(1)
                && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
            {
                rightClickedEnabled = false;
            }
            if (DrawRightClickMenu(hierarchy[i].type, i))
            {
                if (shouldCloseChildWindow)
                    ImGui::EndChild();
                if (shouldPopWindowColor)
                    ImGui::PopStyleColor();
                break;
            }

            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered() && moving.empty())
            {
                moving = hierarchy[i].name;
                moved = false;
            }

            if (moving == hierarchy[i].name)
            {
                if (TryMoveElement(i))
                {
                    if (shouldCloseChildWindow)
                        ImGui::EndChild();
                    if (shouldPopWindowColor)
                        ImGui::PopStyleColor();
                    break;
                }
            }

            if (shouldCloseChildWindow)
                ImGui::EndChild();
            if (shouldPopWindowColor)
                ImGui::PopStyleColor();
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
        if (hierarchy[elementIndex].name == moving && !ImGui::IsWindowHovered())
        {
            int size = GetHierarchyElementSize(elementIndex);
            int dest = elementIndex + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
            if (std::abs(ImGui::GetMouseDragDelta(0).y) >= 12.0f && dest >= 0 && dest + size <= hierarchy.size()
                && hierarchy.size() > 1)
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
                dest = dest > 0 ? dest : 0;

                std::vector<Element> temp = {};
                temp.insert(temp.begin(), hierarchy.begin() + elementIndex, hierarchy.begin() + elementIndex + size);
                hierarchy.erase(hierarchy.begin() + elementIndex, hierarchy.begin() + elementIndex + size);
                hierarchy.insert(hierarchy.begin() + dest, temp.begin(), temp.end());

                ImGui::ResetMouseDragDelta();
                moved = true;
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
                    deletedFolders.push(idToDel);
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
