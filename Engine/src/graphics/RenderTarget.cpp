#include "RenderTarget.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11RenderTarget.h"

std::shared_ptr<rl::RenderTarget> rl::RenderTarget::Create(bool useSwapChain)
{
	switch (Renderer::GetAPI())
	{
	    case GraphicsAPI::DX11:
		    return std::make_shared<DX11RenderTarget>(useSwapChain);
	    default: break;
	}

	//throw error
	return nullptr;
}