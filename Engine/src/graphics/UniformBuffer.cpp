#include "UniformBuffer.h"

#include "GraphicsContext.h"

#ifdef RL_USE_DX11
#include "../drivers/dx11/DX11UniformBuffer.h"
#endif

#ifdef RL_USE_VULKAN
#include "../drivers/vk/VKUniformBuffer.h"
#endif

std::shared_ptr<rl::UniformBuffer> rl::UniformBuffer::Create(uint32_t size, ShaderType shaderType, uint32_t binding,
                                                             const std::weak_ptr<GraphicsContext>& context)
{
    switch (GraphicsContext::GetAPI())
    {
#ifdef RL_USE_DX11
        case GraphicsAPI::DX11:
            return std::make_shared<DX11UniformBuffer>(size, shaderType, binding,
                                                       std::static_pointer_cast<rl::DX11Context>(context.lock()));
#endif

#ifdef RL_USE_VULKAN
        case GraphicsAPI::Vulkan:
            return std::make_shared<VKUniformBuffer>(size, shaderType, binding,
                                                     std::static_pointer_cast<rl::VKContext>(context.lock()));
#endif

        default:
            break;
    }

    // throw error
    return nullptr;
}
