#include "NewProject.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "../Editor.h"
#include "../project/ProjectManager.h"

using namespace rl::ed;

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
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::Begin("New Project", &open, ImGuiWindowFlags_NoDocking))
    {
        ImGui::SetWindowSize(ImVec2(600, 300));

        ImGui::Text("Project Name: ");
        ImGui::InputText("##name", &name);
        name.erase(std::remove(name.begin(), name.end(), ' '), name.end());

        ImGui::Separator();

        if (ImGui::Button("Create", ImVec2(585, 50)))
        {
            ProjectManager::New(name);
            open = false;
        }

        ImGui::End();
    }
}

bool NewProject::IsOpen()
{
    return open;
}
