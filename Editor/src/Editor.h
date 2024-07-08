#pragma once

#include "GuiElement.h"
#include "core/Application.h"
#include "graphics/RenderTarget.h"
#include "imgui.h"
#include "types/OptionalVector.h"

namespace rl::ed
{
    class Editor
    {
    public:
        Editor();
        ~Editor();

        void Render();
        static bool Update();
        static void Exit();

        static bool Playing();
        static void Play();
        static void Pause();

        static void AddGuiElement(const std::weak_ptr<GuiElement>& newElement);

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
}
