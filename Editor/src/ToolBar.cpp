#include "ToolBar.h"

#include <imgui.h>

#include "Editor.h"
#include "project/ProjectManager.h"
#include "windows/Console.h"
#include "windows/SceneHierarchy.h"
#include "windows/SystemsManager.h"
#include "windows/Components.h"

using namespace rl::ed;

void ToolBar::Render()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))
                NewProject::OpenPopup();
            if (ImGui::MenuItem("Open"))
                OpenProject::OpenPopup();
            ImGui::MenuItem("Save");
            ImGui::MenuItem("SaveAs");
            ImGui::Separator();
            if (ImGui::MenuItem("Exit"))
                Editor::Exit();

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows"))
        {
            if (ImGui::MenuItem("Viewport"))
                ShowViewport();
            if (ImGui::MenuItem("Console"))
                Console::OpenWindow();
            if (ImGui::MenuItem("Systems Manager"))
                SystemsManager::OpenWindow();
            if (ImGui::MenuItem("Scene Hierarchy"))
                SceneHierarchy::OpenWindow();
            if(ImGui::MenuItem("Components"))
                Components::OpenWindow();
            ImGui::MenuItem("Asset Browser");

            ImGui::EndMenu();
        }

        // temp
        if (ImGui::MenuItem("Compile"))
            ProjectManager::Compile();
        if (ImGui::MenuItem("Play"))
            Editor::Play();
        if (ImGui::MenuItem("Stop"))
            Editor::Pause();

        ImGui::EndMainMenuBar();
    }
}

bool ToolBar::IsOpen()
{
    return true;
}

void ToolBar::ShowViewport()
{
    viewport = std::make_shared<Viewport>();
    Editor::AddGuiElement(viewport);
}
