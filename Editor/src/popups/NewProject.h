#pragma once

#include <memory>
#include <string>

#include "../GuiElement.h"

namespace rl::editor
{
    class NewProject : public GuiElement
    {
    public:
        ~NewProject() override = default;
        NewProject() = default;

        static void OpenPopup();
        static void ClosePopup();

        void Render() override;
        bool IsOpen() override;

    private:
        static std::shared_ptr<NewProject> popup;
        bool open = true;

        std::string name;
        std::string path;
    };
}
