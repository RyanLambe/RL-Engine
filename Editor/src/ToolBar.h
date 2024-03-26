#pragma once

#include <memory>
#include "GuiElement.h"
#include "windows/Viewport.h"
#include "popups/NewProject.h"
#include "popups/OpenProject.h"

namespace rl::editor {
    class ToolBar : public GuiElement{
    public:
        void Render() override;
        bool IsOpen() override;

    private:

        void ShowViewport();
        std::shared_ptr<Viewport> viewport;

        void NewProject();
        std::shared_ptr<editor::NewProject> newProject;
        void OpenProject();
        std::shared_ptr<editor::OpenProject> openProject;
    };
}
