#include "VKUniformBuffer.h"

namespace rl
{

    VKUniformBuffer::VKUniformBuffer(uint32_t size, ShaderType shaderType, uint32_t binding,
                                     const std::weak_ptr<VKContext>& contextPtr)
    {}

    void VKUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset) {}

}