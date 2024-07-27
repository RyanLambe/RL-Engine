#pragma once

#include <memory>
#include <string>
#include <vector>

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

        std::vector<std::pair<bool, std::string>> systems;
        int moving = -1;
        bool hoveredMoving = true;

        [[nodiscard]] bool TryMoveSystem(int systemIndex);

        void DrawAddSystemMenu();
        void UpdateSystems();
    };
}
