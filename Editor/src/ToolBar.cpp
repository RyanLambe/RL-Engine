#include "ToolBar.h"

#include <imgui.h>

#include "Editor.h"
#include "project/ProjectManager.h"

using namespace rl::editor;

void ToolBar::Render()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))
                NewProject();
            if (ImGui::MenuItem("Open"))
                OpenProject();
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
            ImGui::MenuItem("Scene Hierarchy");
            ImGui::MenuItem("Details");
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
    Editor::CreateGuiElement(viewport);
}

void ToolBar::NewProject()
{
    newProject = std::make_shared<editor::NewProject>();
    Editor::CreateGuiElement(newProject);
}

void ToolBar::OpenProject()
{
    openProject = std::make_shared<editor::OpenProject>();
    Editor::CreateGuiElement(openProject);
}
