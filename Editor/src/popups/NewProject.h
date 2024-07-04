#pragma once

#include <string>

#include "../GuiElement.h"

namespace rl::editor
{
    class NewProject : public GuiElement
    {
    public:
        ~NewProject() override = default;
        NewProject() = default;

        void Render() override;
        bool IsOpen() override;

    private:
        bool open = true;

        std::string name;
        std::string path;
    };
}
