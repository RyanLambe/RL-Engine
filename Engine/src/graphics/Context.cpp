#include "Context.h"

#include "Renderer.h"

#include "../drivers/dx11/dx11Context.h"

std::shared_ptr<rl::Context> rl::Context::Create(std::shared_ptr<Window> window)
{
	switch (Renderer::GetAPI())
	{
        case GraphicsAPI::DX11:
		    return std::make_shared<DX11Context>(window);
	    default: break;
	}

	//throw error
	return nullptr;

}

