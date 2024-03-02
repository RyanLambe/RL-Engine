#include "Renderer.h"

#include "../core/Logger.h"
#include <glm/gtx/string_cast.hpp>

#include "../core/RLResult.h"
#include "../components/MeshComponent.h"
#include "../components/Transform.h"


std::shared_ptr<rl::Context> rl::Renderer::context;
std::shared_ptr<rl::RenderTarget> rl::Renderer::target;

void rl::Renderer::Start(std::shared_ptr<Window> window)
{
    context = Context::Create(std::move(window));
    target = RenderTarget::Create();
    target->Enable();

    std::shared_ptr<Shader> shader = Shader::Create("VertexShader.cso", "PixelShader.cso");
    shader->Enable();

    glm::vec4 test = glm::vec4(0, 1, 0, 1);
    std::shared_ptr<UniformBuffer> ub = UniformBuffer::Create(sizeof(glm::vec4), ShaderType::PixelShader, 0);
    ub->SetData(&test, sizeof(glm::vec3), 0);
}

void rl::Renderer::Render()
{
	target->Clear();
	target->EnableDepthTest();

	// view matrix

	// materials

	// lights

	// draw
    for(auto& mesh : MeshComponent::GetAllComponents()){
        if(!Transform::HasComponent(mesh.getEntity())){
            RL_LOG_WARNING("Mesh Components require Transform components to render.");
            continue;
        }

        mesh.Enable();
        context->DrawIndexed(mesh.GetIndexCount());
    }

	context->Present();
}

// todo: make interchangeable
rl::GraphicsAPI rl::Renderer::GetAPI()
{
	return GraphicsAPI::DX11;
}

void rl::Renderer::Resize(int width, int height) {
    target->Resize(width, height);
}
