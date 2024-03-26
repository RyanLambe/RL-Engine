#include "Renderer.h"

#include "../core/Logger.h"

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

void rl::Renderer::Start(std::shared_ptr<Window> window, bool renderToWindow)
{
    width = window->getWidth();
    height = window->getHeight();

    context = Context::Create(window);

    target = RenderTarget::Create(renderToWindow);

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
    target->Enable();

	// view matrix
    const Camera* cam = Camera::GetMain();
    if(cam == nullptr){
        RL_LOG_ERROR("Camera Required for Rendering.");
        return;
    }
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
}

void rl::Renderer::Present() {
    context->Present();
    target->Clear();
}

void rl::Renderer::Resize(int width, int height) {
    if(width <= 0 || height <= 0)
        return;
    if(width == Renderer::width && height == Renderer::height)
        return;
    Renderer::width = width;
    Renderer::height = height;
    target->Resize(width, height);
}

int rl::Renderer::getWidth() noexcept {
    return width;
}

int rl::Renderer::getHeight() noexcept {
    return height;
}

// todo: make interchangeable
rl::GraphicsAPI rl::Renderer::GetAPI()
{
    return GraphicsAPI::DX11;
}

void *rl::Renderer::GetDXDevice() {
    return context->GetDXDevice();
}

void *rl::Renderer::GetDXContext() {
    return context->GetDXContext();
}

void *rl::Renderer::GetRenderTexture() {
    return target->GetTexture();
}