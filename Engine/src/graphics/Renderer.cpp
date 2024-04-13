#include "Renderer.h"

#include "../core/Logger.h"

#include "../components/Camera.h"
#include "../components/MeshComponent.h"
#include "../components/Transform.h"


rl::Renderer::Renderer(const std::shared_ptr<Window> &window) {

    width = window->getWidth();
    height = window->getHeight();

    context = Context::Create(window.get());
    target = RenderTarget::Create(window, context);


    // temp

    ObjectUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), ShaderType::VertexShader, 0, context);
    SceneUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), ShaderType::VertexShader, 1, context);

    std::shared_ptr<Shader> shader = Shader::Create("VertexShader.cso", "PixelShader.cso", context);
    shader->Enable();

    glm::vec4 test = glm::vec4(0, 1, 0, 1);
    std::shared_ptr<UniformBuffer> ub = UniformBuffer::Create(sizeof(glm::vec4), ShaderType::PixelShader, 0, context);
    ub->SetData(&test, sizeof(glm::vec3), 0);
}

void rl::Renderer::Render()
{
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

void rl::Renderer::RenderToWindow() {
    target->Enable();
    Render();
}

void rl::Renderer::Present() {
    context->Present();
    target->Clear();
}

void rl::Renderer::ResizeTarget(int w, int h) {
    if(w <= 0 || h <= 0)
        return;
    if(w == width && h == height)
        return;
    width = w;
    height = h;
    target->Resize(w, h);
}

void rl::Renderer::EnableTarget() {
    target->Enable();
}

std::weak_ptr<rl::Context> rl::Renderer::GetContext() {
    return context;
}

void *rl::Renderer::GetRenderTexture() {
    return target->GetTexture();
}

void *rl::Renderer::GetDXDevice() {
    return context->GetDXDevice();
}

void *rl::Renderer::GetDXContext() {
    return context->GetDXContext();
}

// todo: make interchangeable
rl::GraphicsAPI rl::Renderer::GetAPI()
{
    return GraphicsAPI::DX11;
}


