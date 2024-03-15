#include "UniformBuffer.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11UniformBuffer.h"

std::shared_ptr<rl::UniformBuffer> rl::UniformBuffer::Create(uint32_t size, ShaderType shaderType, uint32_t binding)
{
    switch (Renderer::GetAPI())
    {
        case GraphicsAPI::DX11:
            return std::make_shared<DX11UniformBuffer>(size, shaderType, binding);
        default: break;
    }

    //throw error
    return nullptr;
}
