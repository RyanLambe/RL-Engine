#pragma once

#include <memory>

#include "Graphics.h"

// allow for different APIs?
#include "dx11.h"

// purpose:
// - create/handle objects
// - calculate light / other render data
// - skybox? handled by camera?

namespace rl::impl {
	class Renderer
	{
	public:
		Renderer() = delete;
		Renderer(const Renderer&) = delete;

		Renderer(HWND hwnd, int width, int height) {
			graphics = std::make_unique<dx11>(hwnd, width, height);
		}

		void Render();



	private:
		std::unique_ptr<Graphics> graphics;
	};
}