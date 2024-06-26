#pragma once

#include <GLFW/glfw3.h>

#include "../../core/Window.h"

#include "glfwInput.h"

namespace rl {
    class glfwWindow : public Window {
    public:
        glfwWindow() = delete;
        glfwWindow(int width, int height, const std::string& title, bool fullscreen);
        ~glfwWindow();

        void Setup() override;
        void EnableContext() override;
        [[nodiscard]] bool Update() override;

        [[nodiscard]] internal::Input* GetInput() const override;

        [[nodiscard]] void* GetHWND() const override;
        [[nodiscard]] void* GetGLFWwindow() const override;

        [[nodiscard]] int GetWidth() const override;
        [[nodiscard]] int GetHeight() const override;

        void SetResizeCallback(rl::RLWindowResizeCallback callback) override;
        void SetFullscreen(bool fullscreen) override;

    private:

        static void internalResizeCallback(GLFWwindow* window, int width, int height);

        glfwWindow* RLWindow = nullptr;
        GLFWwindow* window = nullptr;

        glfwInput input;

        RLWindowResizeCallback externalResizeCallback = nullptr;
        bool isFullscreen;
        int minWidth, minHeight, maxWidth, maxHeight;

    };
}
