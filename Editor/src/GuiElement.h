#pragma once

namespace rl::editor {
    class GuiElement{
    public:
        virtual void Render() = 0;
        virtual bool IsOpen() = 0;
    };
}