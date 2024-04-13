#include "RenderTarget.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11RenderTarget.h"

std::shared_ptr<rl::RenderTarget> rl::RenderTarget::Create(const std::weak_ptr<Window>& window, const std::weak_ptr<Context>& context)
{
	switch (Renderer::GetAPI())
	{
	    case GraphicsAPI::DX11:
		    return std::make_shared<DX11RenderTarget>(window, std::static_pointer_cast<DX11Context>(context.lock()));
	    default: break;
	}

	//throw error
	return nullptr;
}

std::shared_ptr<rl::RenderTarget> rl::RenderTarget::Create(uint32_t width, uint32_t height, const std::weak_ptr<Context> &context) {
    switch (Renderer::GetAPI())
    {
        case GraphicsAPI::DX11:
            return std::make_shared<DX11RenderTarget>(width, height, std::static_pointer_cast<DX11Context>(context.lock()));
        default: break;
    }

    //throw error
    return nullptr;
}
