#include "Components.h"

#include "../Editor.h"
#include "SceneHierarchy.h"

namespace rl::ed
{
    std::shared_ptr<Components> Components::window = nullptr;

    void Components::SelectEntity(rl::Entity entity, const std::string& name)
    {
        window->isSelected = true;
        window->selected = entity;
        (name + '\0').copy((char*)window->name, 256);
    }

    void Components::DeselectEntity()
    {
        window->isSelected = false;
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
            if (!isSelected)
            {
                ImGui::End();
                return;
            }

            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (ImGui::InputText("##name", &name[0], 256))
            {
                SceneHierarchy::SetEntityName(selected, std::string((char*)name));
            }

            ImGui::Separator();

            ImGui::Button("todo: Add components here :)");
        }
        ImGui::End();
    }

    bool Components::IsOpen()
    {
        return open;
    }
}