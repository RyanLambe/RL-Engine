#include "VKRenderTarget.h"

namespace rl
{

    VKRenderTarget::VKRenderTarget(const std::weak_ptr<Window>& windowPtr, const std::weak_ptr<VKContext>& contextPtr)
    {}

    VKRenderTarget::VKRenderTarget(uint32_t width, uint32_t height, const std::weak_ptr<VKContext>& contextPtr) {}

    void VKRenderTarget::Enable() {}

    void VKRenderTarget::Clear() {}

    void VKRenderTarget::Resize(uint32_t width, uint32_t height) {}

    void VKRenderTarget::SetClearColor(const glm::vec4& value) noexcept {}

    void* VKRenderTarget::GetTexture() noexcept
    {
        return nullptr;
    }

}
