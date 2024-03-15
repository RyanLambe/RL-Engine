#pragma once

#include <memory>

namespace rl{

    enum ShaderType{
        VertexShader,
        PixelShader
    };

    class UniformBuffer {
    public:
        static std::shared_ptr<UniformBuffer> Create(uint32_t size, ShaderType shaderType, uint32_t binding);

        virtual void SetData(const void* data, uint32_t size, uint32_t offset) = 0;
    };
}

