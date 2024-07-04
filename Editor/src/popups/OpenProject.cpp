#include "OpenProject.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "../Editor.h"
#include "../project/ProjectManager.h"

using namespace rl::editor;

using namespace rl::editor;

std::shared_ptr<OpenProject> OpenProject::popup = nullptr;

void OpenProject::OpenPopup()
{
    if (!popup)
    {
        popup = std::make_shared<OpenProject>();
    }
    popup->open = true;
    Editor::AddGuiElement(popup);
}

void OpenProject::ClosePopup()
{
    popup->open = false;
}

void OpenProject::Render()
{
    if (ImGui::Begin("Open Project", &open, ImGuiWindowFlags_NoDocking))
    {
        ImGui::SetWindowSize(ImVec2(600, 300));

        ImGui::Text("Project Name: ");
        ImGui::SameLine();
        ImGui::InputText(" ", &name);

        ImGui::Text("Project Directory: ");
        ImGui::SameLine();
        ImGui::InputText("  ", &path);

        if (ImGui::Button("Open"))
        {
            ProjectManager::Open(name, path);
            open = false;
        }

        ImGui::End();
    }
}

bool OpenProject::IsOpen()
{
    return open;
}
