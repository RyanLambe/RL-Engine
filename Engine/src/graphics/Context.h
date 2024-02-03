#pragma once

#include <memory>
#include "../core/Window.h"

namespace rl {

	enum GraphicsAPI
	{
		None = 0,
		DX11 = 1,
		OpenGL = 2
	};

	class Context
	{
	public:

		//todo change HWND to generic?
		static std::shared_ptr<Context> Create(std::shared_ptr<Window> window);
		
		virtual void DrawIndexed(uint32_t size) const noexcept = 0;
		
		virtual void Present() const = 0;
	};
}