#include "VertexBuffer.h"

#include "GraphicsContext.h"

#ifdef RL_USE_DX11
#include "../drivers/dx11/DX11VertexBuffer.h"
#endif

#ifdef RL_USE_VULKAN
#include "../drivers/vk/VKVertexBuffer.h"
#endif

rl::VertexBuffer::~VertexBuffer()
{

}

std::shared_ptr<rl::VertexBuffer> rl::VertexBuffer::Create(const std::vector<Vertex>& data, bool dynamic, const std::weak_ptr<GraphicsContext>& context)
{
	switch (GraphicsContext::GetAPI())
	{
		#ifdef RL_USE_DX11
        case GraphicsAPI::DX11: return std::make_shared<DX11VertexBuffer>(data, dynamic, std::static_pointer_cast<DX11Context>(context.lock()));
		#endif

		#ifdef RL_USE_VULKAN
		case GraphicsAPI::Vulkan: return std::make_shared<VKVertexBuffer>(data, dynamic, std::static_pointer_cast<VKContext>(context.lock()));
		#endif

		default: break;
	}

	//throw error
	return nullptr;
}
