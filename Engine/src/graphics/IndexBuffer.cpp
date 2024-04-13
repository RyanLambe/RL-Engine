#include "IndexBuffer.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11IndexBuffer.h"

std::shared_ptr<rl::IndexBuffer> rl::IndexBuffer::Create(const std::vector<uint32_t>& data, bool dynamic, const std::weak_ptr<Context>& context)
{
	switch (Renderer::GetAPI())
	{
	    case GraphicsAPI::DX11:
		    return std::make_shared<DX11IndexBuffer>(data, dynamic, std::static_pointer_cast<DX11Context>(context.lock()));
	    default: break;
	}

	//throw error
	return nullptr;
}