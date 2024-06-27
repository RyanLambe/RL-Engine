#pragma once

#include "GuiElement.h"
#include "core/Application.h"
#include "graphics/RenderTarget.h"
#include "imgui.h"
#include "types/OptionalVector.h"

namespace rl::editor
{
    class Editor
    {
    public:
        Editor();
        ~Editor();

        void Render();
        bool Update();
        static void Exit();

        static bool Playing();
        static void Play();
        static void Pause();

        static inline void CreateGuiElement(const std::weak_ptr<GuiElement>& element)
        {
            guiElements.push_back(element);
        }

    private:
        static void OnWindowResize(Window* window, int width, int height);

        void SetImGuiStyle();

        static int newWidth;
        static int newHeight;
        static bool resized;
        static bool open;
        static bool playing;

        static std::vector<std::weak_ptr<GuiElement>> guiElements;
        ImGuiIO* io;

        std::shared_ptr<RenderTarget> renderTarget = nullptr;
    };
} // namespace rl::editor
