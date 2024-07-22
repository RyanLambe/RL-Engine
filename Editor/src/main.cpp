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

    toolbar = std::make_shared<ToolBar>();
    Editor::AddGuiElement(toolbar);

    // open default windows
    AssetBrowser::OpenWindow();
    Console::OpenWindow();
    SystemsManager::OpenWindow();
    SceneHierarchy::OpenWindow();
    Components::OpenWindow();

    // temp
    CodeManager::AddSystem(std::filesystem::path("Assets/Example.cpp"), std::filesystem::path("Assets/Example.h"));
    CodeManager::AddComponent(std::filesystem::path("Assets/ExampleComp.cpp"),
                              std::filesystem::path("Assets/ExampleComp.h"));

    // main loop
    while (Editor::Update())
    {
        editor.Render();
        if (Editor::Playing())
        {
            rl::Application::Update();
        }
    }
    return 0;
}