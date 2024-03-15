#include "Renderer.h"

#include "../core/Logger.h"
#include <glm/gtx/string_cast.hpp>

#include "../components/Camera.h"
#include "../core/RLResult.h"
#include "../components/MeshComponent.h"
#include "../components/Transform.h"

int rl::Renderer::width;
int rl::Renderer::height;

std::shared_ptr<rl::Context> rl::Renderer::context;
std::shared_ptr<rl::RenderTarget> rl::Renderer::target;

std::shared_ptr<rl::UniformBuffer> rl::Renderer::ObjectUniformBuffer;
std::shared_ptr<rl::UniformBuffer> rl::Renderer::SceneUniformBuffer;

void rl::Renderer::Start(std::shared_ptr<Window> window)
{
    width = window->getWidth();
    height = window->getHeight();

    context = Context::Create(window);

    target = RenderTarget::Create();
    target->EnableDepthTest();
    target->Enable();

    ObjectUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), ShaderType::VertexShader, 0);
    SceneUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), ShaderType::VertexShader, 1);

    // todo: create shader/material system
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
    const Camera* cam = Camera::GetMain();
    if (!Transform::HasComponent(cam->getEntity())) {
        RL_LOG_WARNING("Camera Components require Transform Components to Render.");
        return;
    }

    const glm::mat4 viewMatrix = cam->GetViewMatrix((float)width, (float)height) * Transform::GetComponent(cam->getEntity()).GetInverseTransformationMatrix();
    SceneUniformBuffer->SetData(&viewMatrix, sizeof(glm::mat4), 0);

	// materials

	// lights

	// draw
    for(auto& mesh : MeshComponent::GetAllComponents()){
        if(!Transform::HasComponent(mesh.getEntity())){
            RL_LOG_WARNING("Mesh Components require Transform Components to Render.");
            continue;
        }

        ObjectUniformBuffer->SetData(&Transform::GetComponent(mesh.getEntity()).GetTransformationMatrix(), sizeof(glm::mat4), 0);

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
    Renderer::width = width;
    Renderer::height = height;
    target->Resize(width, height);
}
