#include "Renderer.h"

void rl::impl::Renderer::Render()
{
	graphics->PrepFrame();
	graphics->Draw();
	graphics->Present();
}
