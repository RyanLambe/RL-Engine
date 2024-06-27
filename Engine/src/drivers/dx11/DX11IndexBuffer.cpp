#include "dx11IndexBuffer.h"

using namespace rl;

DX11IndexBuffer::DX11IndexBuffer(const std::vector<uint32_t>& data, bool dynamic,
                                 const std::weak_ptr<DX11Context>& contextPtr) :
    contextPtr(contextPtr)
{
    isDynamic = dynamic;

    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(uint32_t) * data.size();
    bufferDesc.StructureByteStride = sizeof(uint32_t);
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;

    if (isDynamic)
    {
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }

    D3D11_SUBRESOURCE_DATA initData;
    initData.pSysMem = data.data();
    initData.SysMemPitch = 0;
    initData.SysMemSlicePitch = 0;

    if (auto context = contextPtr.lock())
    {
        DX_LOG_ERROR(context->GetDevice()->CreateBuffer(&bufferDesc, &initData, &indexBuffer));
    }
    else
    {
        RL_THROW_EXCEPTION("Cannot access Context");
    }
}

void DX11IndexBuffer::Enable()
{
    if (auto context = contextPtr.lock())
    {
        context->GetContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    }
    else
    {
        RL_THROW_EXCEPTION("Cannot access Context");
    }
}

void DX11IndexBuffer::Set(const std::vector<uint32_t>& data)
{
    if (!isDynamic)
    {
        D3D11_BUFFER_DESC bufferDesc;
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = sizeof(uint32_t) * data.size();
        bufferDesc.StructureByteStride = sizeof(uint32_t);
        bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA initData;
        initData.pSysMem = data.data();
        initData.SysMemPitch = 0;
        initData.SysMemSlicePitch = 0;

        if (auto context = contextPtr.lock())
        {
            DX_LOG_ERROR(context->GetDevice()->CreateBuffer(&bufferDesc, &initData, &indexBuffer));
        }
        else
        {
            RL_THROW_EXCEPTION("Cannot access Context");
        }
    }
    else
    {
        D3D11_MAPPED_SUBRESOURCE mappedSubResource;
        memset(&mappedSubResource, 0, sizeof(mappedSubResource));

        if (auto context = contextPtr.lock())
        {
            DX_LOG_ERROR(
                context->GetContext()->Map(indexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource));
        }
        else
        {
            RL_THROW_EXCEPTION("Cannot access Context");
        }

        // copy new data
        memcpy(mappedSubResource.pData, data.data(), sizeof(uint32_t) * data.size());

        // cleanup
        if (auto context = contextPtr.lock())
        {
            context->GetContext()->Unmap(indexBuffer.Get(), 0);
        }
        else
        {
            RL_THROW_EXCEPTION("Cannot access Context");
        }
    }
}
