#pragma once

#include <memory>

#include "GraphicsContext.h"

namespace rl
{

    enum ShaderType
    {
        VertexShader,
        PixelShader
    };

    class UniformBuffer
    {
    public:
        virtual ~UniformBuffer() = default;

        static std::shared_ptr<UniformBuffer> Create(uint32_t size, ShaderType shaderType, uint32_t binding,
                                                     const std::weak_ptr<GraphicsContext> &context);

        virtual void SetData(const void *data, uint32_t size, uint32_t offset) = 0;
    };
} // namespace rl
