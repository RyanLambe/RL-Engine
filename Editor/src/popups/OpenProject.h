#pragma once

#include <memory>
#include <string>

#include "../GuiElement.h"

namespace rl::editor
{
    class OpenProject : public GuiElement
    {
    public:
        ~OpenProject() override = default;
        OpenProject() = default;

        static void OpenPopup();
        static void ClosePopup();

        void Render() override;
        bool IsOpen() override;

    private:
        static std::shared_ptr<OpenProject> popup;
        bool open = true;

        std::string name;
        std::string path = R"(C:\Users\ryanl\OneDrive\Documents\RL-EngineTest)"; // todo: remove
    };
}
