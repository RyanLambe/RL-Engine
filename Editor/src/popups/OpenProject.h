#pragma once

#include <string>

#include "../GuiElement.h"

namespace rl::editor {
    class OpenProject : public GuiElement {
    public:
        OpenProject() = default;

        void Render() override;
        bool IsOpen() override;

    private:
        bool open = true;

        std::string name;
        std::string path;
    };
}
