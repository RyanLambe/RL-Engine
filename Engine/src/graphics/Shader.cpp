#include "Shader.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11Shader.h"

std::shared_ptr<rl::Shader> rl::Shader::Create(const std::string &vertexShaderPath, const std::string &pixelShaderPath)
{
    switch (Renderer::GetAPI())
    {
        case GraphicsAPI::DX11:
            return std::make_shared<DX11Shader>(vertexShaderPath, pixelShaderPath);
        default: break;
    }

    //throw error
    return nullptr;
}