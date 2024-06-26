#include "GraphicsContext.h"

#ifdef RL_USE_DX11
#include "../drivers/dx11/DX11Context.h"
#endif
#ifdef RL_USE_VULKAN
#include "../drivers/vk/VKContext.h"
#endif

using namespace rl;

std::shared_ptr<rl::GraphicsContext> rl::GraphicsContext::Create(Window* window)
{
	switch (GraphicsContext::GetAPI())
	{
		#ifdef RL_USE_DX11
        case GraphicsAPI::DX11: return std::make_shared<DX11Context>(window);
		#endif

		#ifdef RL_USE_VULKAN
			case GraphicsAPI::Vulkan: return std::make_shared<VKContext>(window);
		#endif

		default: break;
	}

	//throw error
	return nullptr;

}

GraphicsAPI GraphicsContext::GetAPI() {
    #ifdef RL_USE_DX11
    return GraphicsAPI::DX11;
    #endif

    #ifdef RL_USE_VULKAN
    return GraphicsAPI::Vulkan;
    #endif
}

