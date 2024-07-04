#pragma once

#include <memory>

#include "../GuiElement.h"

namespace rl::editor
{
    class Console : public GuiElement
    {
    public:
        ~Console() override = default;

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

    private:
        static std::shared_ptr<Console> window;
        bool open = true;
    };
}
