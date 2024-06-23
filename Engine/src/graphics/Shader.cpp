#include "Shader.h"

#include "Renderer.h"

#ifdef RL_USE_DX11
#include "../drivers/dx11/DX11Shader.h"
#endif

#ifdef RL_USE_VULKAN
#include "../drivers/vk/VKShader.h"
#endif

std::shared_ptr<rl::Shader> rl::Shader::Create(const std::string &vertexShaderPath, const std::string &pixelShaderPath, const std::weak_ptr<Context>& context)
{
    switch (Renderer::GetAPI())
    {
        #ifdef RL_USE_DX11
        case GraphicsAPI::DX11: return std::make_shared<DX11Shader>(vertexShaderPath, pixelShaderPath, std::static_pointer_cast<DX11Context>(context.lock()));
        #endif

        #ifdef RL_USE_VULKAN
        case GraphicsAPI::Vulkan: return std::make_shared<VKShader>(vertexShaderPath, pixelShaderPath, std::static_pointer_cast<VKContext>(context.lock()));
        #endif

        default: break;
    }

    //throw error
    return nullptr;
}