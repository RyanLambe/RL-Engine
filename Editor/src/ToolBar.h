#pragma once

#include <memory>

#include "GuiElement.h"
#include "popups/NewProject.h"
#include "popups/OpenProject.h"
#include "windows/Viewport.h"

namespace rl::editor
{
    class ToolBar : public GuiElement
    {
    public:
        void Render() override;
        bool IsOpen() override;

    private:
        void ShowViewport();
        std::shared_ptr<Viewport> viewport;
    };
}
