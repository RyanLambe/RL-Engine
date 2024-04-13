#pragma once

#include <GLFW/glfw3.h>
#include "../../core/Window.h"

namespace rl {
    class glfwWindow : public Window {
    public:
        glfwWindow() = delete;
        glfwWindow(int width, int height, const std::string& title, bool fullscreen);
        ~glfwWindow();

        [[nodiscard]]
        bool Update() const noexcept override;
        void Setup() override;

        [[nodiscard]]
        void* getHWND() const noexcept override;
        [[nodiscard]]
        void* getGLFWwindow() const noexcept override;

        [[nodiscard]]
        int getWidth() const noexcept override;
        [[nodiscard]]
        int getHeight() const noexcept override;

        void setResizeCallback(rl::RLWindowResizeCallback callback) noexcept override;
        void setFullscreen(bool fullscreen) noexcept override;

        static GLFWwindow* GetActiveGLFWWindow() noexcept;
        static glfwWindow* GetActiveRLWindow() noexcept;

    private:

        static void internalResizeCallback(GLFWwindow* window, int width, int height);

        static glfwWindow* RLWindow;
        GLFWwindow* window = nullptr;

        RLWindowResizeCallback externalResizeCallback = nullptr;
        bool isFullscreen;
        int minWidth, minHeight, maxWidth, maxHeight;

    };
}
