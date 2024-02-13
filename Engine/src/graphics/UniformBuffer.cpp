//
// Created by ryanl on 2024-02-11.
//

#include "UniformBuffer.h"

#include "../drivers/dx11/dx11UniformBuffer.h"

using namespace rl;

std::shared_ptr<UniformBuffer> UniformBuffer::Create(uint32_t size, ShaderType shaderType, uint32_t binding) {
    return std::make_shared<DX11UniformBuffer>(size, shaderType, binding);
}
