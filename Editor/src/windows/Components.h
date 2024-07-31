#pragma once

#include <Engine.h>

#include <memory>
#include <string>

#include "../GuiElement.h"
#include "../tools/CodeManager.h"

namespace rl::ed
{
    class Components : public GuiElement
    {
    public:
        ~Components() override = default;

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

    private:
        static std::shared_ptr<Components> window;
        bool open = true;

        char name[256] = "";

        void DrawAddComponentMenu();
        void DrawRightClickMenu(const std::string& componentName);
        void UpdateComponent(const std::string& componentName);
    };
}
