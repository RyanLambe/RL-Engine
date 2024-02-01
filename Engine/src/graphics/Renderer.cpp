#include "Renderer.h"

#include "../core/Logger.h"
#include <glm/gtx/string_cast.hpp>

#include "../core/RLResult.h"

void rl::Renderer::Render()
{
	target->Clear();
	target->EnableDepthTest();

	// view matrix

	// materials

	// lights

	// draw
	context->DrawIndexed(tempSize);

	context->Present();
}

// todo: make interchangeable
rl::GraphicsAPI rl::Renderer::GetAPI()
{
	return GraphicsAPI::DX11;
}
