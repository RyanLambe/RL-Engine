#include "IndexBuffer.h"

#include "Renderer.h"

#ifdef RL_USE_DX11
#include "../drivers/dx11/dx11IndexBuffer.h"
#endif

std::shared_ptr<rl::IndexBuffer> rl::IndexBuffer::Create(const std::vector<uint32_t>& data, bool dynamic, const std::weak_ptr<Context>& context)
{
	switch (Renderer::GetAPI())
	{
		#ifdef RL_USE_DX11
	    case GraphicsAPI::DX11: return std::make_shared<DX11IndexBuffer>(data, dynamic, std::static_pointer_cast<DX11Context>(context.lock()));
		#endif

		default: break;
	}

	//throw error
	return nullptr;
}