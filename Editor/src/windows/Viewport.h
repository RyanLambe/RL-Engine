#pragma once

#include "../GuiElement.h"
#include "Engine.h"

namespace rl::editor
{
    class Viewport : public GuiElement
    {
    public:
        void Render() override;
        bool IsOpen() override;

    private:
        bool open = true;
    };
} // namespace rl::editor
