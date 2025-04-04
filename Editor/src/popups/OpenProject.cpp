#include "OpenProject.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "../Editor.h"
#include "../project/ProjectManager.h"

using namespace rl::ed;

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
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::Begin("Open Project", &open, ImGuiWindowFlags_NoDocking))
    {
        ImGui::SetWindowSize(ImVec2(600, 700));

        static int selected = 0;
        if (ImGui::BeginChild("ScrollableArea", ImVec2(585, 600), true, ImGuiWindowFlags_HorizontalScrollbar)) {
            for(int i = 0; i < ProjectManager::GetProjects().size(); i++) {
                if (ImGui::Selectable(ProjectManager::GetProjects()[i].filename().string().c_str(), selected == i)) {
                    selected = i;
                }
            }
            ImGui::EndChild();
        }

        if (ImGui::Button("Open", ImVec2(585, 50)))
        {
            ProjectManager::Open(ProjectManager::GetProjects()[selected]);
            open = false;
        }

        ImGui::End();
    }
}

bool OpenProject::IsOpen()
{
    return open;
}
