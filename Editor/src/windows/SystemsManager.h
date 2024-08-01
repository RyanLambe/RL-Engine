#pragma once

#include <memory>
#include <string>
#include <vector>

#include <types/Types.h>

#include "../GuiElement.h"

namespace rl::ed
{
    class SystemsManager : public GuiElement
    {
    public:
        ~SystemsManager() override = default;

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

    private:
        static std::shared_ptr<SystemsManager> window;
        bool open = true;

        bool hoveredMoving = true;
        i64 moving = -1;

        [[nodiscard]] bool TryMoveSystem(int systemIndex);
        static void DrawAddSystemMenu();
    };
}
