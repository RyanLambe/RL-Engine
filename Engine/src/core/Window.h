#pragma once

#include <memory>
#include <string>

namespace rl {
    class Window;
    typedef void (*RLWindowResizeCallback)(Window* window, int width, int height);

    class Window {
    public:
        static std::shared_ptr<Window> Create(int width, int height, const std::string& title, bool fullscreen);

        // polls events and returns if window should close
        [[nodiscard]]
        virtual bool Update() const noexcept = 0;

        [[nodiscard]]
        virtual void* getHWND() const noexcept = 0;
        [[nodiscard]]
        virtual int getWidth() const noexcept = 0;
        [[nodiscard]]
        virtual int getHeight() const noexcept = 0;

        virtual void setFullscreen(bool fullscreen) noexcept = 0;
        virtual void setResizeCallback(RLWindowResizeCallback callback) noexcept = 0;
    };
}
