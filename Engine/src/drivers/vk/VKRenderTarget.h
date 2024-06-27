#pragma once

#include "../../graphics/RenderTarget.h"
#include "VKContext.h"

namespace rl
{
    class VKRenderTarget : public RenderTarget
    {
    public:
        VKRenderTarget(const std::weak_ptr<Window>& windowPtr, const std::weak_ptr<VKContext>& contextPtr);
        VKRenderTarget(uint32_t width, uint32_t height, const std::weak_ptr<VKContext>& contextPtr);

        void Enable() override;
        void Clear() override;

        void Resize(uint32_t width, uint32_t height) override;

        void SetClearColor(const glm::vec4& value) noexcept override;

        [[nodiscard]] void* GetTexture() noexcept override;

    private:
    };
} // namespace rl
