#pragma once

#include "VKContext.h"

#include "../../graphics/UniformBuffer.h"

namespace rl {
    class VKUniformBuffer : public UniformBuffer {
    public:
        VKUniformBuffer(uint32_t size, ShaderType shaderType, uint32_t binding, const std::weak_ptr<VKContext>& contextPtr);

        void SetData(const void *data, uint32_t size, uint32_t offset) override;

    private:

    };
}
