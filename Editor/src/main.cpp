#include "Editor.h"
#include "ToolBar.h"
#include "project/ProjectManager.h"
#include "tools/CodeManager.h"
#include "windows/AssetBrowser.h"
#include "windows/Components.h"
#include "windows/Console.h"
#include "windows/SceneHierarchy.h"
#include "windows/SystemsManager.h"

using namespace rl::ed;

std::shared_ptr<ToolBar> toolbar;

int main()
{
    Editor editor = Editor();
    ProjectManager projectManager = ProjectManager();
    ProjectManager::SetProjectsFolder("./projects/");

    toolbar = std::make_shared<ToolBar>();
    Editor::AddGuiElement(toolbar);

    // open default windows
    AssetBrowser::OpenWindow();
    Console::OpenWindow();
    SystemsManager::OpenWindow();
    SceneHierarchy::OpenWindow();
    Components::OpenWindow();

    CodeManager::AddBuiltInComponent(std::filesystem::path("/include/components/Transform.h"));
    CodeManager::AddBuiltInComponent(std::filesystem::path("/include/components/Camera.h"));
    CodeManager::AddBuiltInComponent(std::filesystem::path("/include/components/MeshComponent.h"));

    CodeManager::AddBuiltInSystem(std::filesystem::path("/include/systems/Renderer.h"));

    // main loop
    while (Editor::Update())
    {
        editor.Render();
        if (Editor::Playing())
        {
            rl::Application::Update();
        }
    }
    ProjectManager::SaveProject();
    return 0;
}