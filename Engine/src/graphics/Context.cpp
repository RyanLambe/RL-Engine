#include "Context.h"

#include "Renderer.h"

#ifdef RL_USE_DX11
#include "../drivers/dx11/DX11Context.h"
#endif
#ifdef RL_USE_VULKAN
#include "../drivers/vk/VKContext.h"
#endif

std::shared_ptr<rl::Context> rl::Context::Create(Window* window)
{
	switch (Renderer::GetAPI())
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

