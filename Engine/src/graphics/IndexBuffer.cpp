#include "IndexBuffer.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11-IndexBuffer.h"

std::shared_ptr<rl::IndexBuffer> rl::IndexBuffer::Create(const std::vector<uint32_t>& data, bool dynamic)
{
	switch (Renderer::GetAPI())
	{
	case GraphicsAPI::DX11:
		return std::make_shared<impl::DX11IndexBuffer>(data, dynamic);
	default: break;
	}

	//throw error
	return nullptr;
}