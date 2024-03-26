#pragma once

#include "../GuiElement.h"

namespace rl::editor {
    class Viewport : public GuiElement {
    public:
        void Render() override;
        bool IsOpen() override;

    private:
        bool open = true;
    };
}
