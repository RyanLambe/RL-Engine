#pragma once

#include <memory>
#include <utility>

#include "Context.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "RenderTarget.h"

#include "../types/Mesh.h"
#include "UniformBuffer.h"
#include "Shader.h"


namespace rl {
	class Renderer
	{
	public:
		Renderer() = delete;
		Renderer(const Renderer&) = delete;

		explicit Renderer(std::shared_ptr<Window> window) {
			context = Context::Create(std::move(window));
			target = RenderTarget::Create();
			target->Enable();

			Mesh mesh = Mesh();
			mesh.ImportObj("test.obj");

            std::shared_ptr<Shader> shader = Shader::Create("VertexShader.cso", "PixelShader.cso");
            shader->Enable();

			std::shared_ptr<VertexBuffer> vb = VertexBuffer::Create(mesh.getVertices());
			vb->Enable();

			std::shared_ptr<IndexBuffer> ib = IndexBuffer::Create(mesh.getIndices());
			ib->Enable();

            glm::vec4 test = glm::vec4(0, 1, 0, 1);
            std::shared_ptr<UniformBuffer> ub = UniformBuffer::Create(sizeof(glm::vec4), ShaderType::PixelShader, 0);
            ub->SetData(&test, sizeof(glm::vec3), 0);

			tempSize = (uint32_t)mesh.getIndices().size();
		}

		void Render();
        void Resize(int width, int height);

		static GraphicsAPI GetAPI();

	private:
		uint32_t tempSize;

		std::shared_ptr<rl::Context> context;
		std::shared_ptr<rl::RenderTarget> target;
	};
}