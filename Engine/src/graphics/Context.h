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

		static std::shared_ptr<Context> Create(Window* window);
		
		virtual void DrawIndexed(uint32_t size) const noexcept = 0;
		
		virtual void Present() const = 0;

        [[nodiscard]] virtual void* GetDXDevice() const = 0;
        [[nodiscard]] virtual void* GetDXContext() const = 0;
	};
}