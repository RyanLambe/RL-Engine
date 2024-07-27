#include "Components.h"

#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <limits>

#include "../Editor.h"
#include "SceneHierarchy.h"

namespace rl::ed
{
    std::shared_ptr<Components> Components::window = nullptr;

    void Components::SelectEntity(rl::Entity entity, const std::string& name)
    {
        window->isSelected = true;
        window->isFolderSelected = false;
        window->selected = entity;
        (name + '\0').copy((char*)window->name, 256);
    }

    void Components::SelectFolder(size_t folder, const std::string& name)
    {
        window->isSelected = true;
        window->isFolderSelected = true;
        window->selected = folder;
        (name + '\0').copy((char*)window->name, 256);
    }

    void Components::Deselect()
    {
        window->isSelected = false;
        window->isFolderSelected = false;
        window->selected = 0;
        window->name[0] = '\0';
    }

    bool Components::IsSelected(size_t val, bool folder)
    {
        if (!window->isSelected)
            return false;
        if (window->isFolderSelected != folder)
            return false;
        return val == window->selected;
    }

    void Components::OpenWindow()
    {
        if (!window)
        {
            window = std::make_shared<Components>();
        }
        window->open = true;
        Editor::AddGuiElement(window);
    }

    void Components::CloseWindow()
    {
        window->open = false;
    }

    void Components::Render()
    {
        if (ImGui::Begin("Components", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse))
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
            if (!isSelected)
            {
                ImGui::End();
                return;
            }

            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (ImGui::InputText("##name", &name[0], 256))
            {
                for(char& i : name){
                    if(i == '\0')
                        break;
                    if(i == '_')
                        i = ' ';
                }
                if (!isFolderSelected)
                    SceneHierarchy::SetEntityName(selected, std::string((char*)name));
                else
                    SceneHierarchy::SetFolderName(selected, std::string((char*)name));
            }

            if (isFolderSelected)
            {
                ImGui::Separator();
                ImGui::End();
                return;
            }

            if (!data.contains(selected))
            {
                data[selected] = {};
                componentOrder[selected] = {};
            }

            for (auto& componentName : componentOrder[selected])
            {
                auto& component = data[selected][componentName];
                ImGui::PushFont(Editor::GetWingdingFont());
                if (ImGui::Button(("T##" + componentName + std::to_string(selected)).c_str(), ImVec2(0, 0)))
                {
                    CodeManager::RemoveComponent(componentName, selected);
                    ImGui::PopFont();
                    data[selected].erase(componentName);
                    componentOrder[selected].erase(
                        std::find(componentOrder[selected].begin(), componentOrder[selected].end(), componentName));
                    break;
                }
                ImGui::PopFont();
                ImGui::SameLine();
                ImGui::SeparatorText(Editor::FormatName(componentName).c_str());
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) && ImGui::IsMouseClicked(1))
                {
                    ImGui::OpenPopup(("RightClick" + componentName + std::to_string(selected)).c_str());
                }
                DrawRightClickMenu(componentName);

                float size = ImGui::GetContentRegionAvail().x;
                ImGui::Columns(2, "locations", false);
                ImGui::SetColumnWidth(0, size * 0.3f);

                UpdateComponent(componentName);
                for (const auto& property : CodeManager::GetProperties(componentName))
                {
                    ImGui::Text("%s", Editor::FormatName(property.second).c_str());
                    ImGui::NextColumn();

                    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                    switch (property.first)
                    {
                        case VariableType::Unknown:
                            ImGui::Text("UNKNOWN_TYPE");
                            break;
                        case VariableType::I8:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].I8, 1, std::numeric_limits<i8>::min(),
                                               std::numeric_limits<i8>::max()))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].I8);
                            }
                            break;
                        case VariableType::I16:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].I16, 1,
                                               std::numeric_limits<i16>::min(), std::numeric_limits<i16>::max()))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].I16);
                            }
                            break;
                        case VariableType::I32:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].I32, 1,
                                               std::numeric_limits<i32>::min(), std::numeric_limits<i32>::max()))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].I32);
                            }
                            break;
                        case VariableType::I64:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].I64, 1))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].I64);
                            }
                            break;
                        case VariableType::U8:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].U8, 1, std::numeric_limits<u8>::min(),
                                               std::numeric_limits<u8>::max()))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].U8);
                            }
                            break;
                        case VariableType::U16:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].U16, 1,
                                               std::numeric_limits<u16>::min(), std::numeric_limits<u16>::max()))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].U16);
                            }
                            break;
                        case VariableType::U32:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].U32, 1,
                                               std::numeric_limits<u32>::min(), std::numeric_limits<int>::max()))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].U32);
                            }
                            break;
                        case VariableType::U64:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].U64, 1,
                                               std::numeric_limits<u64>::min(), std::numeric_limits<int>::max()))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].U64);
                            }
                            break;
                        case VariableType::F32:
                            if (ImGui::DragFloat(("##in-" + componentName + property.second).c_str(),
                                                 (float*)&component[property.second].F32, 0.1))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].F32);
                            }
                            break;
                        case VariableType::F64:
                            if (ImGui::DragFloat(("##in-" + componentName + property.second).c_str(),
                                                 (float*)&component[property.second].F64, 0.1))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].F64);
                            }
                            break;
                        case VariableType::VEC2:
                            if (ImGui::DragFloat2(("##in-" + componentName + property.second).c_str(),
                                                  (float*)&component[property.second].Vec2, 0.1))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].Vec2);
                            }
                            break;
                        case VariableType::VEC3:
                            if (ImGui::DragFloat3(("##in-" + componentName + property.second).c_str(),
                                                  (float*)&component[property.second].Vec3, 0.1))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].Vec3);
                            }
                            break;
                        case VariableType::VEC4:
                            if (ImGui::DragFloat4(("##in-" + componentName + property.second).c_str(),
                                                  (float*)&component[property.second].Vec4, 0.1))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].Vec4);
                            }
                            break;
                        case VariableType::QUAT:
                            if (ImGui::DragFloat4(("##in-" + componentName + property.second).c_str(),
                                                  (float*)&component[property.second].Quat, 0.1))
                            {
                                CodeManager::SetComponentValue(property.first, componentName, property.second, selected,
                                                               component[property.second].Quat);
                            }
                            break;
                    }
                    ImGui::NextColumn();
                }
                ImGui::Columns();
            }

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            ImGui::Separator();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
            if (ImGui::Button("Add Component", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                ImGui::OpenPopup("Add Component Menu");
            DrawAddComponentMenu();
        }
        ImGui::End();
    }

    bool Components::IsOpen()
    {
        return open;
    }

    void Components::DrawAddComponentMenu()
    {
        if (ImGui::BeginPopup("Add Component Menu"))
        {
            ImGui::Text("Add Component:\t\t\t\t\t");
            ImGui::Separator();

            for (const auto& component : CodeManager::GetComponents())
            {
                if (data[selected].contains(component))
                    continue;

                if (ImGui::Button(Editor::FormatName(component).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                {
                    data[selected][component] = {};
                    componentOrder[selected].push_back(component);
                    CodeManager::AddComponent(component, selected);
                    UpdateComponent(component);

                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
    }

    void Components::DrawRightClickMenu(const std::string& componentName)
    {
        if (ImGui::BeginPopup(("RightClick" + componentName + std::to_string(selected)).c_str()))
        {
            ImGui::Text("%s\t\t\t", Editor::FormatName(componentName).c_str());
            ImGui::Separator();

            if (ImGui::Button("Refresh"))
            {
                UpdateComponent(componentName);
            }

            if (componentOrder[selected].front() != componentName)
            {
                if (ImGui::Button("Move Up"))
                {
                    for (int i = 1; i < componentOrder[selected].size(); i++)
                    {
                        if (componentOrder[selected][i] == componentName)
                        {
                            const std::string temp = componentOrder[selected][i - 1];
                            componentOrder[selected][i - 1] = componentOrder[selected][i];
                            componentOrder[selected][i] = temp;
                            break;
                        }
                    }
                    ImGui::CloseCurrentPopup();
                }
            }

            if (componentOrder[selected].back() != componentName)
            {
                if (ImGui::Button("Move Down"))
                {
                    for (int i = 0; i < componentOrder[selected].size() - 1; i++)
                    {
                        if (componentOrder[selected][i] == componentName)
                        {
                            const std::string temp = componentOrder[selected][i + 1];
                            componentOrder[selected][i + 1] = componentOrder[selected][i];
                            componentOrder[selected][i] = temp;
                            break;
                        }
                    }
                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
    }

    void Components::UpdateComponent(const std::string& componentName)
    {
        Quaternion quatTemp; // only used for quat properties

        for (const auto& property : CodeManager::GetProperties(componentName))
        {
            switch (property.first)
            {
                case VariableType::Unknown:
                    return;
                case VariableType::I8:
                    data[selected][componentName][property.second].I8 = 0;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].I8);
                    break;
                case VariableType::I16:
                    data[selected][componentName][property.second].I16 = 0;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].I16);
                    break;
                case VariableType::I32:
                    data[selected][componentName][property.second].I32 = 0;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].I32);
                    break;
                case VariableType::I64:
                    data[selected][componentName][property.second].I64 = 0;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].I64);
                    break;
                case VariableType::U8:
                    data[selected][componentName][property.second].U8 = 0;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].U8);
                    break;
                case VariableType::U16:
                    data[selected][componentName][property.second].U16 = 0;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].U16);
                    break;
                case VariableType::U32:
                    data[selected][componentName][property.second].U32 = 0;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].U32);
                    break;
                case VariableType::U64:
                    data[selected][componentName][property.second].U64 = 0;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].U64);
                    break;
                case VariableType::F32:
                    //data[selected][componentName][property.second].F32 = 0;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].F32);
                    break;
                case VariableType::F64:
                    data[selected][componentName][property.second].F64 = 0.0f;
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].F64);
                    break;
                case VariableType::VEC2:
                    data[selected][componentName][property.second].Vec2 = Vec2(0);
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].Vec2);
                    break;
                case VariableType::VEC3:
                    data[selected][componentName][property.second].Vec3 = Vec3(0);
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].Vec3);
                    break;
                case VariableType::VEC4:
                    data[selected][componentName][property.second].Vec4 = Vec4(0);
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].Vec4);
                    break;
                case VariableType::QUAT:
                    data[selected][componentName][property.second].Quat = Quaternion(1, 0, 0, 0);
                    CodeManager::GetComponentValue(property.first, componentName, property.second, selected,
                                                   &data[selected][componentName][property.second].Quat);
                    break;
            }
        }
    }
}