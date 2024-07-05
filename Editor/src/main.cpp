#include "Editor.h"
#include "ToolBar.h"
#include "project/ProjectManager.h"
#include "windows/Console.h"
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
    Console::OpenWindow();
    SystemsManager::OpenWindow();

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