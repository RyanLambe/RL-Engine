#include "Context.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11-Context.h"

std::shared_ptr<rl::Context> rl::Context::Create(void* hwnd, int width, int height)
{

	switch (Renderer::GetAPI())
	{
	case GraphicsAPI::DX11:
		return std::make_shared<impl::DX11Context>((HWND)hwnd, width, height);
	default: break;
	}

	//throw error
	return nullptr;

}

