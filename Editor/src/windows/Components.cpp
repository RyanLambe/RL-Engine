#include "Components.h"

#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <limits>

#include "../Editor.h"
#include "SceneHierarchy.h"

namespace rl::ed
{
    std::shared_ptr<Components> Components::window = nullptr;

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
            if (!Application::GetSceneManager().IsSceneOpen())
            {
                ImGui::Text("No scene is open.");
                ImGui::End();
                return;
            }

            Entity selected = SceneHierarchy::GetSelected();
            if (selected == NullEntity)
            {
                ImGui::End();
                return;
            }

            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            EntityData* selectedData = Scene::GetScene().GetEntityData(selected);
            (selectedData->name + '\0').copy((char*)name, 256);
            if (ImGui::InputText("##name", &name[0], 256))
            {
                for (char& i : name)
                {
                    if (i == '\0')
                        break;
                    if (i == '_')
                        i = ' ';
                }
                selectedData->name = std::string((char*)name);
            }

            for (auto& componentName : selectedData->componentOrder)
            {
                auto& component = selectedData->componentData[componentName];
                ImGui::PushFont(Editor::GetWingdingFont());
                if (ImGui::Button(("T##" + componentName + std::to_string(selected)).c_str(), ImVec2(0, 0)))
                {
                    Application::GetGameContext().RemoveComponent(componentName, selected);
                    ImGui::PopFont();
                    selectedData->componentData.erase(componentName);
                    selectedData->componentOrder.erase(std::find(selectedData->componentOrder.begin(),
                                                                 selectedData->componentOrder.end(), componentName));
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

                Application::GetGameContext().UpdateSceneWithComponentData(componentName,
                                                                           SceneHierarchy::GetSelected());
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
                                               (int*)&component[property.second].data.I8, 1,
                                               std::numeric_limits<i8>::min(), std::numeric_limits<i8>::max()))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.I8);
                            }
                            break;
                        case VariableType::I16:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].data.I16, 1,
                                               std::numeric_limits<i16>::min(), std::numeric_limits<i16>::max()))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.I16);
                            }
                            break;
                        case VariableType::I32:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].data.I32, 1,
                                               std::numeric_limits<i32>::min(), std::numeric_limits<i32>::max()))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.I32);
                            }
                            break;
                        case VariableType::I64:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].data.I64, 1))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.I64);
                            }
                            break;
                        case VariableType::U8:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].data.U8, 1,
                                               std::numeric_limits<u8>::min(), std::numeric_limits<u8>::max()))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.U8);
                            }
                            break;
                        case VariableType::U16:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].data.U16, 1,
                                               std::numeric_limits<u16>::min(), std::numeric_limits<u16>::max()))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.U16);
                            }
                            break;
                        case VariableType::U32:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].data.U32, 1,
                                               std::numeric_limits<u32>::min(), std::numeric_limits<int>::max()))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.U32);
                            }
                            break;
                        case VariableType::U64:
                            if (ImGui::DragInt(("##in-" + componentName + property.second).c_str(),
                                               (int*)&component[property.second].data.U64, 1,
                                               std::numeric_limits<u64>::min(), std::numeric_limits<int>::max()))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.U64);
                            }
                            break;
                        case VariableType::F32:
                            if (ImGui::DragFloat(("##in-" + componentName + property.second).c_str(),
                                                 (float*)&component[property.second].data.F32, 0.1))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.F32);
                            }
                            break;
                        case VariableType::F64:
                            if (ImGui::DragFloat(("##in-" + componentName + property.second).c_str(),
                                                 (float*)&component[property.second].data.F64, 0.1))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.F64);
                            }
                            break;
                        case VariableType::VEC2:
                            if (ImGui::DragFloat2(("##in-" + componentName + property.second).c_str(),
                                                  (float*)&component[property.second].data.Vec2, 0.1))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.Vec2);
                            }
                            break;
                        case VariableType::VEC3:
                            if (ImGui::DragFloat3(("##in-" + componentName + property.second).c_str(),
                                                  (float*)&component[property.second].data.Vec3, 0.1))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.Vec3);
                            }
                            break;
                        case VariableType::VEC4:
                            if (ImGui::DragFloat4(("##in-" + componentName + property.second).c_str(),
                                                  (float*)&component[property.second].data.Vec4, 0.1))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.Vec4);
                            }
                            break;
                        case VariableType::QUAT:
                            if (ImGui::DragFloat4(("##in-" + componentName + property.second).c_str(),
                                                  (float*)&component[property.second].data.Quat, 0.1))
                            {
                                Application::GetGameContext().SetComponentValue(property.first, componentName,
                                                                                property.second, selected,
                                                                                component[property.second].data.Quat);
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
            if (!ProjectManager::IsProjectCompiled())
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::Text("Add Component:\t\t\t\t\t");
            ImGui::Separator();

            EntityData* selectedData = Scene::GetScene().GetEntityData(SceneHierarchy::GetSelected());

            for (const auto& component : CodeManager::GetComponents())
            {
                if (selectedData->componentData.contains(component))
                    continue;

                if (ImGui::Button(Editor::FormatName(component).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
                {
                    Scene::GetScene().InitComponentData(component, CodeManager::GetProperties(component),
                                                        SceneHierarchy::GetSelected());
                    Application::GetGameContext().AddComponent(component, SceneHierarchy::GetSelected());
                    Application::GetGameContext().UpdateSceneWithComponentData(component,
                                                                               SceneHierarchy::GetSelected());

                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
    }

    void Components::DrawRightClickMenu(const std::string& componentName)
    {
        if (ImGui::BeginPopup(("RightClick" + componentName + std::to_string(SceneHierarchy::GetSelected())).c_str()))
        {
            if (!ProjectManager::IsProjectCompiled())
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::Text("%s\t\t\t", Editor::FormatName(componentName).c_str());
            ImGui::Separator();

            EntityData* selectedData = Scene::GetScene().GetEntityData(SceneHierarchy::GetSelected());

            if (ImGui::Button("Refresh"))
            {
                Application::GetGameContext().UpdateSceneWithComponentData(componentName,
                                                                           SceneHierarchy::GetSelected());
            }

            if (selectedData->componentOrder.front() != componentName)
            {
                if (ImGui::Button("Move Up"))
                {
                    for (int i = 1; i < selectedData->componentOrder.size(); i++)
                    {
                        if (selectedData->componentOrder[i] == componentName)
                        {
                            const std::string temp = selectedData->componentOrder[i - 1];
                            selectedData->componentOrder[i - 1] = selectedData->componentOrder[i];
                            selectedData->componentOrder[i] = temp;
                            break;
                        }
                    }
                    ImGui::CloseCurrentPopup();
                }
            }

            if (selectedData->componentOrder.back() != componentName)
            {
                if (ImGui::Button("Move Down"))
                {
                    for (int i = 0; i < selectedData->componentOrder.size() - 1; i++)
                    {
                        if (selectedData->componentOrder[i] == componentName)
                        {
                            const std::string temp = selectedData->componentOrder[i + 1];
                            selectedData->componentOrder[i + 1] = selectedData->componentOrder[i];
                            selectedData->componentOrder[i] = temp;
                            break;
                        }
                    }
                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
    }
}