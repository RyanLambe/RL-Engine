#pragma once

#include <memory>

#include "Context.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "RenderTarget.h"

#include "../types/Mesh.h"


namespace rl {
	class Renderer
	{
	public:
		Renderer() = delete;
		Renderer(const Renderer&) = delete;

		Renderer(void* hwnd, int width, int height) {
			context = Context::Create(hwnd, width, height);
			target = RenderTarget::Create();
			target->Enable();

			Mesh mesh = Mesh();
			mesh.ImportObj("test.obj");

			std::shared_ptr<VertexBuffer> vb = VertexBuffer::Create(mesh.getVertices());
			vb->Enable();

			std::shared_ptr<IndexBuffer> ib = IndexBuffer::Create(mesh.getIndices());
			ib->Enable();

			tempSize = (uint32_t)mesh.getIndices().size();
		}

		void Render();

		static GraphicsAPI GetAPI();

	private:
		uint32_t tempSize;

		std::shared_ptr<rl::Context> context;
		std::shared_ptr<rl::RenderTarget> target;
	};
}