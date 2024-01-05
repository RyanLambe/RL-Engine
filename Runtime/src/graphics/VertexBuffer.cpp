#include "VertexBuffer.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11-VertexBuffer.h"

std::shared_ptr<rl::VertexBuffer> rl::VertexBuffer::Create(const std::vector<Vertex>& data, bool dynamic)
{
	switch (Renderer::GetAPI())
	{
		case GraphicsAPI::DX11: 
			return std::make_shared<impl::DX11VertexBuffer>(data, dynamic);
		default: break;
	}

	//throw error
	return nullptr;
}