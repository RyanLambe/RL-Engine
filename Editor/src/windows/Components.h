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
        static void SelectFolder(size_t folder, const std::string& name);
        static void Deselect();

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

    private:
        static std::shared_ptr<Components> window;
        bool open = true;

        bool isSelected = false;
        bool isFolderSelected = false;
        size_t selected;

        char name[256] = "";
    };
}
