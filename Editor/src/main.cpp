#include "Editor.h"
#include "project/ProjectManager.h"
#include "ToolBar.h"

using namespace rl;

std::shared_ptr<editor::ToolBar> toolbar;

int main() {

    editor::Editor editor = editor::Editor();
    editor::ProjectManager projectManager = editor::ProjectManager();

    toolbar = std::make_shared<editor::ToolBar>();
    editor::Editor::CreateGuiElement(toolbar);

    // main loop
    while (editor.Update()){
        if(editor::Editor::Playing())
            Application::GetSystemManager().UpdateSystems();
        editor.Render();
    }
    return 0;
}