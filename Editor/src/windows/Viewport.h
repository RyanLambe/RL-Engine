#pragma once

#include "../GuiElement.h"
#include "Engine.h"

namespace rl::editor {
    class Viewport : public GuiElement {
    public:
        Viewport();
        void Render() override;
        bool IsOpen() override;

    private:
        bool open = true;
        std::shared_ptr<RenderTarget> target = nullptr;
    };
}
