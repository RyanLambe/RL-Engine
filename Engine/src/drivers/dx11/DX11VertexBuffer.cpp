#include "dx11VertexBuffer.h"

using namespace rl;

rl::DX11VertexBuffer::DX11VertexBuffer(const std::vector<Vertex>& data, bool dynamic,
                                       const std::weak_ptr<DX11Context>& contextPtr) :
    contextPtr(contextPtr), isDynamic(dynamic)
{
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(Vertex) * data.size();
    bufferDesc.StructureByteStride = sizeof(Vertex);
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
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
        DX_LOG_ERROR(context->GetDevice()->CreateBuffer(&bufferDesc, &initData, &vertexBuffer));
    }
    else
    {
        RL_THROW_EXCEPTION("Cannot access Context");
    }
}

void DX11VertexBuffer::Enable()
{
    UINT offset = 0;
    UINT stride = sizeof(Vertex);
    if (auto context = contextPtr.lock())
    {
        context->GetContext()->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    }
    else
    {
        RL_THROW_EXCEPTION("Cannot access Context");
    }
}

void DX11VertexBuffer::Set(const std::vector<Vertex>& data)
{
    if (!isDynamic)
    {
        D3D11_BUFFER_DESC bufferDesc;
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = sizeof(Vertex) * data.size();
        bufferDesc.StructureByteStride = sizeof(Vertex);
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA initData;
        initData.pSysMem = data.data();
        initData.SysMemPitch = 0;
        initData.SysMemSlicePitch = 0;

        if (auto context = contextPtr.lock())
        {
            DX_LOG_ERROR(context->GetDevice()->CreateBuffer(&bufferDesc, &initData, &vertexBuffer));
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
                context->GetContext()->Map(vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource));
        }
        else
        {
            RL_THROW_EXCEPTION("Cannot access Context");
        }

        // copy new data
        memcpy(mappedSubResource.pData, data.data(), sizeof(Vertex) * data.size());

        // cleanup
        if (auto context = contextPtr.lock())
        {
            context->GetContext()->Unmap(vertexBuffer.Get(), 0);
        }
        else
        {
            RL_THROW_EXCEPTION("Cannot access Context");
        }
    }
}
