#include "VertexBuffer.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11VertexBuffer.h"

std::shared_ptr<rl::VertexBuffer> rl::VertexBuffer::Create(const std::vector<Vertex>& data, bool dynamic, const std::weak_ptr<Context>& context)
{
	switch (Renderer::GetAPI())
	{
        case GraphicsAPI::DX11:
			return std::make_shared<DX11VertexBuffer>(data, dynamic, std::static_pointer_cast<DX11Context>(context.lock()));
		default: break;
	}

	//throw error
	return nullptr;
}