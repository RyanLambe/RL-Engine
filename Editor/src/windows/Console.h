#pragma once

#include <memory>
#include <string>

#include "../GuiElement.h"

namespace rl::ed
{
    class Console : public GuiElement
    {
    public:
        ~Console() override = default;

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

        static void UpdateBuildLogs();

    private:
        static std::shared_ptr<Console> window;
        bool open = true;

        static std::string cmakeLog;
        static std::string buildLog;

        static void DrawLogger();
    };
}
