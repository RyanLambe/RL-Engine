#include "VertexBuffer.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11VertexBuffer.h"

std::shared_ptr<rl::VertexBuffer> rl::VertexBuffer::Create(const std::vector<Vertex>& data, bool dynamic)
{
	switch (Renderer::GetAPI())
	{
		#ifdef RL_USE_DX11
        case GraphicsAPI::DX11: return std::make_shared<DX11VertexBuffer>(data, dynamic);
		#endif

		default: break;
	}

	//throw error
	return nullptr;
}