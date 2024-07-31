#pragma once

#include <imgui.h>
#include <types/Types.h>

#include <filesystem>
#include <memory>
#include <queue>
#include <vector>

#include "../GuiElement.h"
#include "ecs/ComponentType.h"

namespace rl::ed
{
    class SceneHierarchy : public GuiElement
    {
    public:
        ~SceneHierarchy() override = default;

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

        Entity GetSelected();

    private:
        void DrawEntity(Entity entity);
        void DrawSeparator(Entity entity);
        void DrawRightClickMenu();

        float GetEntityDepth(Entity entity);

        bool popupOpen = false;
        ImVec2 nextHoverRectPos = ImVec2(0, 0);
        float hoverRectOffset = 5; // should be turned to setting
        Entity moving = NullEntity;
        Entity selected = NullEntity;

        static std::shared_ptr<SceneHierarchy> window;
        bool open = true;
    };
}
