#include "Shader.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11Shader.h"

std::shared_ptr<rl::Shader> rl::Shader::Create(const std::string &vertexShaderPath, const std::string &pixelShaderPath, const std::weak_ptr<Context>& context)
{
    switch (Renderer::GetAPI())
    {
        case GraphicsAPI::DX11:
            return std::make_shared<DX11Shader>(vertexShaderPath, pixelShaderPath, std::static_pointer_cast<DX11Context>(context.lock()));
        default: break;
    }

    //throw error
    return nullptr;
}