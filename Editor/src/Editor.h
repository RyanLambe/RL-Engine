#pragma once

#include "core/Window.h"
#include "graphics/RenderTarget.h"
#include "imgui.h"
#include "GuiElement.h"
#include "types/OptionalVector.h"
#include "graphics/Renderer.h"

namespace rl::editor {
    class Editor {
    public:

        Editor();
        ~Editor();

        void Render();
        bool Update();
        static void Exit();

        static bool Playing();
        static void Play();
        static void Pause();

        static inline void CreateGuiElement(const std::weak_ptr<GuiElement>& element) {
            guiElements.push_back(element);
        }

        static Renderer* GetRenderer();

    private:

        static void OnWindowResize(Window* window, int width, int height);

        void SetImGuiStyle();

        static int newWidth;
        static int newHeight;
        static bool resized;
        static bool open;
        static bool playing;

        std::shared_ptr<Window> window;
        static std::unique_ptr<Renderer> renderer;
        static std::vector<std::weak_ptr<GuiElement>> guiElements;
        ImGuiIO* io;
    };
}
