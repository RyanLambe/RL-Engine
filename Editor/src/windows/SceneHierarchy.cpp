#include "SceneHierarchy.h"

#include "../Editor.h"

namespace rl::ed{
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

            if(ImGui::Button("New Folder")){
                // todo: all folders should end with "##fN" where 'N' is the id of the folder
                hierarchy.emplace_back(ElementType::Folder, nextFolder, "Folder: " + std::to_string(nextFolder));
                hierarchy.emplace_back(ElementType::FolderEnd, nextFolder, "Folder: " + std::to_string(nextFolder));
                nextFolder++;
            }
            ImGui::SameLine();
            if(ImGui::Button("New Entity")){
                // todo: all entities should end with "##eN" where 'N' is the id of the Entity
                hierarchy.emplace_back(ElementType::Entity, nextEntity, std::to_string(nextEntity));
                nextEntity++;
            }

            std::vector<bool> treeVisibleStack;
            treeVisibleStack.push_back(true);
            float cursorPos = ImGui::GetCursorPosX();

            for(int i = 0; i < hierarchy.size(); i++){

                switch (hierarchy[i].type) {
                    case ElementType::Entity:
                        if(treeVisibleStack.back()){
                            ImGui::SetCursorPosX(cursorPos);
                            ImGui::Selectable(hierarchy[i].name.c_str());
                        }
                        break;

                    case ElementType::Folder:
                        if(treeVisibleStack.back()){
                            ImGui::SetCursorPosX(cursorPos);
                            if(ImGui::Selectable((hierarchy[i].name.c_str()))){
                                hierarchy[i].enabled = !hierarchy[i].enabled;
                            }
                            treeVisibleStack.push_back(hierarchy[i].enabled);
                            cursorPos += 16;
                        }
                        else
                            treeVisibleStack.push_back(false);
                        break;

                    case ElementType::FolderEnd:
                        if(treeVisibleStack.back()){
                            ImGui::SetCursorPosX(cursorPos);
                            ImGui::Separator();
                        }
                        hierarchy[i].enabled = treeVisibleStack.back();
                        treeVisibleStack.pop_back();
                        cursorPos -= 16;
                        continue;
                }
                if(hierarchy[i].type == ElementType::FolderEnd)
                    continue;

                if(ImGui::IsMouseDown(0) && ImGui::IsItemHovered() && moving.empty()){
                    moving = hierarchy[i].name;
                }

                if (hierarchy[i].name == moving && !ImGui::IsItemHovered())
                {
                    int size = GetHierarchyElementSize(i);
                    int dest = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                    if (dest >= 0 && dest + size <= hierarchy.size() && hierarchy.size() > 1)
                    {
                        if(hierarchy[i].name != hierarchy[dest].name && hierarchy[dest].type == ElementType::Folder && !hierarchy[dest].enabled){
                            dest += GetHierarchyElementSize(dest) - 1;
                        }
                        else if(hierarchy[i].name != hierarchy[dest].name && hierarchy[dest].type == ElementType::FolderEnd && !hierarchy[dest].enabled){
                            dest -= GetHierarchyElementSize(dest) + 1;
                        }
                        dest = std::max(dest, 0);

                        std::vector<Element> temp = {};
                        temp.insert(temp.begin(), hierarchy.begin() + i, hierarchy.begin() + i + size);
                        hierarchy.erase(hierarchy.begin() + i, hierarchy.begin() + i + size);
                        hierarchy.insert(hierarchy.begin() + dest, temp.begin(), temp.end());

                        ImGui::ResetMouseDragDelta();
                        break;
                    }
                }
            }

            if(ImGui::IsMouseReleased(0)){
                moving = "";
            }
        }
        ImGui::End();
    }

    bool SceneHierarchy::IsOpen()
    {
        return open;
    }

    int SceneHierarchy::GetHierarchyElementSize(int element) const {
        int size = 1;

        if(hierarchy[element].type == ElementType::Folder){
            int subLevel = 1;
            for(int j = element + 1; j < hierarchy.size(); j++){
                if(hierarchy[j].type == ElementType::Folder)
                    subLevel++;
                else if(hierarchy[j].type == ElementType::FolderEnd)
                    subLevel--;
                size++;

                if(subLevel <= 0)
                    break;
            }
        }

        return size;
    }
}
