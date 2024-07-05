#pragma once

namespace rl::ed
{
    class GuiElement
    {
    public:
        virtual ~GuiElement() = default;

        virtual void Render() = 0;
        virtual bool IsOpen() = 0;
    };
}