#pragma once

#include <memory>

#include "../GuiElement.h"

namespace rl::ed {
    class SystemsManager : public GuiElement {
    public:
        ~SystemsManager() override = default;

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

    private:
        static std::shared_ptr<SystemsManager> window;
        bool open = true;

    };
}
