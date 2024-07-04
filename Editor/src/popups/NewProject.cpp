#include "NewProject.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "../Editor.h"
#include "../project/ProjectManager.h"

using namespace rl::editor;

std::shared_ptr<NewProject> NewProject::popup = nullptr;

void NewProject::OpenPopup()
{
    if (!popup)
    {
        popup = std::make_shared<NewProject>();
    }
    popup->open = true;
    Editor::AddGuiElement(popup);
}

void NewProject::ClosePopup()
{
    popup->open = false;
}

void NewProject::Render()
{
    if (ImGui::Begin("New Project", &open, ImGuiWindowFlags_NoDocking))
    {
        ImGui::SetWindowSize(ImVec2(600, 300));

        ImGui::Text("Project Name: ");
        ImGui::SameLine();
        ImGui::InputText(" ", &name);

        ImGui::Text("Project Directory: ");
        ImGui::SameLine();
        ImGui::InputText("  ", &path);

        if (ImGui::Button("Create"))
        {
            ProjectManager::New(name, path);
            open = false;
        }

        ImGui::End();
    }
}

bool NewProject::IsOpen()
{
    return open;
}
