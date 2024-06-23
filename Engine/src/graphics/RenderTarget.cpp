#include "RenderTarget.h"

#include "Renderer.h"

#ifdef RL_USE_DX11
#include "../drivers/dx11/DX11RenderTarget.h"
#endif

#ifdef RL_USE_VULKAN
#include "../drivers/vk/VKRenderTarget.h"
#endif

rl::RenderTarget::~RenderTarget()
{

}

std::shared_ptr<rl::RenderTarget> rl::RenderTarget::Create(const std::weak_ptr<Window>& window, const std::weak_ptr<Context>& context)
{
	switch (Renderer::GetAPI())
	{
		#ifdef RL_USE_DX11
	    case GraphicsAPI::DX11: return std::make_shared<DX11RenderTarget>(window, std::static_pointer_cast<DX11Context>(context.lock()));
		#endif

		#ifdef RL_USE_VULKAN
		case GraphicsAPI::Vulkan: return std::make_shared<VKRenderTarget>(window, std::static_pointer_cast<VKContext>(context.lock()));
		#endif

	    default: break;
	}

	//throw error
	return nullptr;
}

std::shared_ptr<rl::RenderTarget> rl::RenderTarget::Create(uint32_t width, uint32_t height, const std::weak_ptr<Context> &context) {
    switch (Renderer::GetAPI())
    {
		#ifdef RL_USE_DX11
        case GraphicsAPI::DX11: return std::make_shared<DX11RenderTarget>(width, height, std::static_pointer_cast<DX11Context>(context.lock()));
		#endif

		#ifdef RL_USE_VULKAN
		case GraphicsAPI::Vulkan: return std::make_shared<VKRenderTarget>(width, height, std::static_pointer_cast<VKContext>(context.lock()));
		#endif

        default: break;
    }

    //throw error
    return nullptr;
}
