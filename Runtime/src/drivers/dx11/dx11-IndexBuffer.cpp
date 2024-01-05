#include "dx11-IndexBuffer.h"

#include "dx11-Context.h"
#include "../../Debug.h"

using namespace rl::impl;

DX11IndexBuffer::DX11IndexBuffer(const std::vector<uint32_t>& data, bool dynamic)
{
	isDynamic = dynamic;

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(uint32_t) * data.size();
	bufferDesc.StructureByteStride = sizeof(uint32_t);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	if (isDynamic) {
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data.data();
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	Debug::logErrorCode(DX11Context::GetDevice()->CreateBuffer(&bufferDesc, &initData, &indexBuffer));
}

void DX11IndexBuffer::Enable()
{
	DX11Context::GetContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void DX11IndexBuffer::Set(const std::vector<uint32_t>& data)
{
	if (!isDynamic) {
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

		Debug::logErrorCode(DX11Context::GetDevice()->CreateBuffer(&bufferDesc, &initData, &indexBuffer));
	}
	else {
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		memset(&mappedSubResource, 0, sizeof(mappedSubResource));

		Debug::logErrorCode(DX11Context::GetContext()->Map(indexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource));

		//copy new data
		memcpy(mappedSubResource.pData, data.data(), sizeof(uint32_t) * data.size());

		//cleanup
		DX11Context::GetContext()->Unmap(indexBuffer.Get(), 0);
	}
}
