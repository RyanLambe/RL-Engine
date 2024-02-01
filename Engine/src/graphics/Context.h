#pragma once

#include <memory>

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
		static std::shared_ptr<Context> Create(void* hwnd, int width, int height);
		
		virtual void DrawIndexed(uint32_t size) const noexcept = 0;
		
		virtual void Present() const = 0;
	};
}