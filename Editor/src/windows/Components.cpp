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
            if (ImGui::IsMouseClicked(0) && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
            {
                //Deselect();
            }
            if (!isSelected)
            {
                ImGui::End();
                return;
            }

            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (ImGui::InputText("##name", &name[0], 256))
            {
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
                data[selected] = {};

            for (auto& component : data[selected])
            {
                ImGui::PushFont(Editor::GetWingdingFont());
                if (ImGui::Button("T", ImVec2(0, 0)))
                {
                    CodeManager::RemoveComponent(component.first, selected);
                    data[selected].erase(component.first);
                    ImGui::PopFont();
                    break;
                }
                ImGui::PopFont();
                ImGui::SameLine();
                ImGui::SeparatorText(FormatName(component.first).c_str());

                float size = ImGui::GetContentRegionAvail().x;
                ImGui::Columns(2, "locations", false);
                ImGui::SetColumnWidth(0, size * 0.3f);

                for (const auto& property : CodeManager::GetProperties(component.first))
                {
                    ImGui::Text("%s", FormatName(property.second).c_str());
                    ImGui::NextColumn();

                    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                    switch (property.first)
                    {
                        case VariableType::Unknown:
                            ImGui::Text("UNKNOWN_TYPE");
                            break;
                        case VariableType::I8:
                            if (ImGui::DragInt(("##in-" + component.first + property.second).c_str(),
                                               (int*)&component.second[property.second].I8, 1,
                                               std::numeric_limits<i8>::min(), std::numeric_limits<i8>::max()))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].I8);
                            }
                            break;
                        case VariableType::I16:
                            if (ImGui::DragInt(("##in-" + component.first + property.second).c_str(),
                                               (int*)&component.second[property.second].I16, 1,
                                               std::numeric_limits<i16>::min(), std::numeric_limits<i16>::max()))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].I16);
                            }
                            break;
                        case VariableType::I32:
                            if (ImGui::DragInt(("##in-" + component.first + property.second).c_str(),
                                               (int*)&component.second[property.second].I32, 1,
                                               std::numeric_limits<i32>::min(), std::numeric_limits<i32>::max()))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].I32);
                            }
                            break;
                        case VariableType::I64:
                            if (ImGui::DragInt(("##in-" + component.first + property.second).c_str(),
                                               (int*)&component.second[property.second].I64, 1))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].I64);
                            }
                            break;
                        case VariableType::U8:
                            if (ImGui::DragInt(("##in-" + component.first + property.second).c_str(),
                                               (int*)&component.second[property.second].U8, 1,
                                               std::numeric_limits<u8>::min(), std::numeric_limits<u8>::max()))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].U8);
                            }
                            break;
                        case VariableType::U16:
                            if (ImGui::DragInt(("##in-" + component.first + property.second).c_str(),
                                               (int*)&component.second[property.second].U16, 1,
                                               std::numeric_limits<u16>::min(), std::numeric_limits<u16>::max()))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].U16);
                            }
                            break;
                        case VariableType::U32:
                            if (ImGui::DragInt(("##in-" + component.first + property.second).c_str(),
                                               (int*)&component.second[property.second].U32, 1,
                                               std::numeric_limits<u32>::min(), std::numeric_limits<int>::max()))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].U32);
                            }
                            break;
                        case VariableType::U64:
                            if (ImGui::DragInt(("##in-" + component.first + property.second).c_str(),
                                               (int*)&component.second[property.second].U64, 1,
                                               std::numeric_limits<u64>::min(), std::numeric_limits<int>::max()))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].U64);
                            }
                            break;
                        case VariableType::F32:
                            if (ImGui::DragFloat(("##in-" + component.first + property.second).c_str(),
                                                 (float*)&component.second[property.second].F32, 1))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].F32);
                            }
                            break;
                        case VariableType::F64:
                            if (ImGui::DragFloat(("##in-" + component.first + property.second).c_str(),
                                                 (float*)&component.second[property.second].F64, 1))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].F64);
                            }
                            break;
                        case VariableType::VEC2:
                            if (ImGui::DragFloat2(("##in-" + component.first + property.second).c_str(),
                                                  (float*)&component.second[property.second].Vec2, 1))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].Vec2);
                            }
                            break;
                        case VariableType::VEC3:
                            if (ImGui::DragFloat3(("##in-" + component.first + property.second).c_str(),
                                                  (float*)&component.second[property.second].Vec3, 1))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].Vec3);
                            }
                            break;
                        case VariableType::VEC4:
                            if (ImGui::DragFloat4(("##in-" + component.first + property.second).c_str(),
                                                  (float*)&component.second[property.second].Vec4, 1))
                            {
                                CodeManager::SetValue(property.first, component.first, property.second, selected,
                                                      component.second[property.second].Vec4);
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

                if (ImGui::Button(component.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                {
                    data[selected][component] = {};
                    CodeManager::AddComponent(component, selected);

                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
    }

    std::string Components::FormatName(const std::string& name)
    {
        std::string out;
        for (int i = 0; i < name.size(); i++)
        {
            if (i == 0)
            {
                out += (i8)toupper(name[i]);
                continue;
            }
            if (name[i] == '_')
            {
                out += ' ';
                continue;
            }
            if (name[i - 1] != toupper(name[i - 1]) && name[i] == toupper(name[i]))
                out += ' ';
            out += name[i];
        }
        return out;
    }
}