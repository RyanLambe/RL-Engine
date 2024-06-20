#include "UniformBuffer.h"

#include "Renderer.h"

#ifdef RL_USE_DX11
#include "../drivers/dx11/dx11UniformBuffer.h"
#endif

std::shared_ptr<rl::UniformBuffer> rl::UniformBuffer::Create(uint32_t size, ShaderType shaderType, uint32_t binding, const std::weak_ptr<Context>& context)
{
    switch (Renderer::GetAPI())
    {
        #ifdef RL_USE_DX11
        case GraphicsAPI::DX11: return std::make_shared<DX11UniformBuffer>(size, shaderType, binding, std::static_pointer_cast<rl::DX11Context>(context.lock()));
        #endif

        default: break;
    }

    //throw error
    return nullptr;
}
