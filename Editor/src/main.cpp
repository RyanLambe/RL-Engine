#include "Editor.h"
#include "ToolBar.h"
#include "project/ProjectManager.h"

using namespace rl::editor;

std::shared_ptr<ToolBar> toolbar;

int main()
{
    Editor editor = Editor();
    ProjectManager projectManager = ProjectManager();

    toolbar = std::make_shared<ToolBar>();
    Editor::AddGuiElement(toolbar);

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