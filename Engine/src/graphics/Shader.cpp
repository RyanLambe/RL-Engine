#include "Shader.h"

#include "../drivers/dx11/dx11Shader.h"

using namespace rl;

std::shared_ptr<Shader> Shader::Create(const std::string &vertexShaderPath, const std::string &pixelShaderPath) {
    return std::make_shared<DX11Shader>(vertexShaderPath, pixelShaderPath);
}