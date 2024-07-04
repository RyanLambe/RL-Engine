#pragma once

namespace rl::editor
{
    class GuiElement
    {
    public:
        virtual ~GuiElement() = default;

        virtual void Render() = 0;
        virtual bool IsOpen() = 0;
    };
}