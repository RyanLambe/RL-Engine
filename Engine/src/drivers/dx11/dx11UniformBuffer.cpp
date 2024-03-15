#include "dx11UniformBuffer.h"
#include "dx11Context.h"


rl::DX11UniformBuffer::DX11UniformBuffer(uint32_t size, ShaderType shaderType, uint32_t binding) : shaderType(shaderType), binding(binding) {

    if(size == 0)
        RL_THROW_EXCEPTION("Cannot create Uniform Buffer of size 0");
    if(size % 4 != 0)
        RL_THROW_EXCEPTION("Uniform Buffer size must be a multiple of 4");

    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.ByteWidth = size;
    bufferDesc.MiscFlags = 0;

    //create buffer
    DX_LOG_ERROR(DX11Context::GetDevice()->CreateBuffer(&bufferDesc, nullptr, &buffer));
}

void rl::DX11UniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset) {

    D3D11_MAPPED_SUBRESOURCE mappedSubResource;
    memset(&mappedSubResource, 0, sizeof(mappedSubResource));

    DX_LOG_ERROR(DX11Context::GetContext()->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource));

    memcpy((char*)mappedSubResource.pData + offset, data, size);

    DX11Context::GetContext()->Unmap(buffer.Get(), 0);

    switch(shaderType){
        case PixelShader:
            DX11Context::GetContext()->PSSetConstantBuffers(binding, 1, buffer.GetAddressOf());
            break;

        case VertexShader:
            DX11Context::GetContext()->VSSetConstantBuffers(binding, 1, buffer.GetAddressOf());
            break;
    }
}
