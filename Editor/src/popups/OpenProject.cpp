#include "OpenProject.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "../project/ProjectManager.h"

using namespace rl::editor;

void OpenProject::Render() {

    if(ImGui::Begin("Open Project", &open, ImGuiWindowFlags_NoDocking)){

        ImGui::SetWindowSize(ImVec2(600, 300));

        ImGui::Text("Project Name: ");
        ImGui::SameLine();
        ImGui::InputText(" ", &name);

        ImGui::Text("Project Directory: ");
        ImGui::SameLine();
        ImGui::InputText("  ", &path);

        if(ImGui::Button("Open")){
            ProjectManager::Open(name, path);
            open = false;
        }

        ImGui::End();
    }
}

bool OpenProject::IsOpen() {
    return open;
}
