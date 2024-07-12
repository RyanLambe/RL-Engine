#pragma once

#include <Engine.h>

#include <memory>
#include <string>

#include "../GuiElement.h"

namespace rl::ed
{
    class Components : public GuiElement
    {
    public:
        ~Components() override = default;

        static void SelectEntity(rl::Entity entity, const std::string& name);
        static void DeselectEntity();

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

    private:
        static std::shared_ptr<Components> window;
        bool open = true;

        bool isSelected = false;
        rl::Entity selected;
        char name[256] = "";
    };
}
