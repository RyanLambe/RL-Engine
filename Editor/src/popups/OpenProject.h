#pragma once

#include <string>

#include "../GuiElement.h"

namespace rl::editor
{
    class OpenProject : public GuiElement
    {
    public:
        ~OpenProject() override = default;
        OpenProject() = default;

        void Render() override;
        bool IsOpen() override;

    private:
        bool open = true;

        std::string name;
        std::string path = R"(C:\Users\ryanl\OneDrive\Documents\RL-EngineTest)"; // todo: remove
    };
}
