#include "dx11UniformBuffer.h"

rl::DX11UniformBuffer::DX11UniformBuffer(uint32_t size, ShaderType shaderType, uint32_t binding,
                                         const std::weak_ptr<DX11Context> &contextPtr) :
    shaderType(shaderType), binding(binding), contextPtr(contextPtr)
{
    if (size == 0)
        RL_THROW_EXCEPTION("Cannot create Uniform Buffer of size 0");
    if (size % 4 != 0)
        RL_THROW_EXCEPTION("Uniform Buffer size must be a multiple of 4");

    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.ByteWidth = size;
    bufferDesc.MiscFlags = 0;

    // create buffer
    if (auto context = contextPtr.lock())
    {
        DX_LOG_ERROR(context->GetDevice()->CreateBuffer(&bufferDesc, nullptr, &buffer));
    }
    else
    {
        RL_THROW_EXCEPTION("Cannot access Context");
    }
}

void rl::DX11UniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset)
{
    auto context = contextPtr.lock();
    if (!context)
    {
        RL_THROW_EXCEPTION("Cannot access Context");
    }

    D3D11_MAPPED_SUBRESOURCE mappedSubResource;
    memset(&mappedSubResource, 0, sizeof(mappedSubResource));

    DX_LOG_ERROR(context->GetContext()->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource));

    memcpy((char *)mappedSubResource.pData + offset, data, size);

    context->GetContext()->Unmap(buffer.Get(), 0);

    switch (shaderType)
    {
        case PixelShader:
            context->GetContext()->PSSetConstantBuffers(binding, 1, buffer.GetAddressOf());
            break;

        case VertexShader:
            context->GetContext()->VSSetConstantBuffers(binding, 1, buffer.GetAddressOf());
            break;
    }
}
