#pragma once
#include <glm/vec4.hpp>
#include <memory>

#include "GraphicsContext.h"

namespace rl
{
    class RenderTarget
    {
    public:
        virtual ~RenderTarget() = default;

        static std::shared_ptr<RenderTarget> Create(const std::weak_ptr<Window>& window,
                                                    const std::weak_ptr<GraphicsContext>& context);
        static std::shared_ptr<RenderTarget> Create(uint32_t width, uint32_t height,
                                                    const std::weak_ptr<GraphicsContext>& context);

        virtual void Enable() = 0;
        virtual void Clear() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual void SetClearColor(const glm::vec4& value) noexcept = 0;

        [[nodiscard]] virtual void* GetTexture() noexcept = 0;
    };
}
