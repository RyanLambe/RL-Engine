#pragma once

#include <memory>
#include <string>

#include "../GuiElement.h"

namespace rl::ed
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
    };
}
