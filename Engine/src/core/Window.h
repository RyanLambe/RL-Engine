#pragma once

#include <memory>
#include <string>
#include "Input.h"

namespace rl {
    class Window;
    typedef void (*RLWindowResizeCallback)(Window* window, int width, int height);

    class Window {
    public:
        static std::shared_ptr<Window> Create(int width, int height, const std::string& title, bool fullscreen);

        // polls events and returns if window should close
        virtual void Setup() = 0;
        virtual void EnableContext() = 0;
        [[nodiscard]] virtual bool Update() = 0;

        [[nodiscard]] virtual internal::Input* GetInput() const = 0;

        [[nodiscard]] virtual void* GetHWND() const = 0;
        [[nodiscard]] virtual void* GetGLFWwindow() const = 0;

        [[nodiscard]] virtual int GetWidth() const = 0;
        [[nodiscard]] virtual int GetHeight() const = 0;

        virtual void SetFullscreen(bool fullscreen) = 0;
        virtual void SetResizeCallback(RLWindowResizeCallback callback) = 0;
    };
}
