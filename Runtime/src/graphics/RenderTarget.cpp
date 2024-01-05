#include "RenderTarget.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11-RenderTarget.h"

std::shared_ptr<rl::RenderTarget> rl::RenderTarget::Create()
{
	switch (Renderer::GetAPI())
	{
	case GraphicsAPI::DX11:
		return std::make_shared<impl::DX11RenderTarget>();
	default: break;
	}

	//throw error
	return nullptr;
}

std::shared_ptr<rl::RenderTarget> rl::RenderTarget::Create(uint32_t width, uint32_t height)
{
	switch (Renderer::GetAPI())
	{
	case GraphicsAPI::DX11:
		return std::make_shared<impl::DX11RenderTarget>(width, height);
	default: break;
	}

	//throw error
	return nullptr;
}