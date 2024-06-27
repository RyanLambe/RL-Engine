#include "IndexBuffer.h"

#include "GraphicsContext.h"

#ifdef RL_USE_DX11
#include "../drivers/dx11/DX11IndexBuffer.h"
#endif

#ifdef RL_USE_VULKAN
#include "../drivers/vk/VKIndexBuffer.h"
#endif

std::shared_ptr<rl::IndexBuffer> rl::IndexBuffer::Create(const std::vector<uint32_t> &data, bool dynamic,
                                                         const std::weak_ptr<GraphicsContext> &context)
{
    switch (GraphicsContext::GetAPI())
    {
#ifdef RL_USE_DX11
        case GraphicsAPI::DX11:
            return std::make_shared<DX11IndexBuffer>(data, dynamic,
                                                     std::static_pointer_cast<DX11Context>(context.lock()));
#endif

#ifdef RL_USE_VULKAN
        case GraphicsAPI::Vulkan:
            return std::make_shared<VKIndexBuffer>(data, dynamic, std::static_pointer_cast<VKContext>(context.lock()));
#endif

        default:
            break;
    }

    // throw error
    return nullptr;
}
