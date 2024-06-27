#include "Renderer.h"

#include "../components/Camera.h"
#include "../components/MeshComponent.h"
#include "../components/Transform.h"
#include "../core/Application.h"
#include "../graphics/Shader.h"

namespace rl
{
    void Renderer::Start()
    {
        // temp
        ObjectUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), ShaderType::VertexShader, 0,
                                                    Application::GetGraphicsContextPtr());
        SceneUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), ShaderType::VertexShader, 1,
                                                   Application::GetGraphicsContextPtr());

        std::shared_ptr<Shader> shader
            = Shader::Create("VertexShader.cso", "PixelShader.cso", Application::GetGraphicsContextPtr());
        shader->Enable();

        glm::vec4 test = glm::vec4(0, 1, 0, 1);
        std::shared_ptr<UniformBuffer> ub = UniformBuffer::Create(sizeof(glm::vec4), ShaderType::PixelShader, 0,
                                                                  Application::GetGraphicsContextPtr());
        ub->SetData(&test, sizeof(glm::vec3), 0);
    }

    void Renderer::Update()
    {
        glm::mat4 viewMatrix;
        for (const auto& cam : Camera::GetAllComponents())
        {
            if (cam.GetRenderTarget() == nullptr)
            {
                RL_LOG_WARNING("Please set render destination via Camera.RenderToWindow "
                               "or Camera.RenderToTarget.");
                continue;
            }
            if (!Transform::HasComponent(cam.GetEntity()))
            {
                RL_LOG_WARNING("Camera Components require Transform Components to Render.");
                return;
            }

            // update render target
            cam.GetRenderTarget()->Enable();
            cam.GetRenderTarget()->Clear();

            // get view matrix
            viewMatrix = cam.GetViewMatrix((float)cam.GetWidth(), (float)cam.GetHeight())
                         * Transform::GetComponent(cam.GetEntity()).GetInverseTransformationMatrix();
            SceneUniformBuffer->SetData(&viewMatrix, sizeof(glm::mat4), 0);

            // materials

            // lights

            // draw
            for (auto& mesh : MeshComponent::GetAllComponents())
            {
                if (!Transform::HasComponent(mesh.GetEntity()))
                {
                    RL_LOG_WARNING("Mesh Components require Transform Components to Render.");
                    continue;
                }

                ObjectUniformBuffer->SetData(&Transform::GetComponent(mesh.GetEntity()).GetTransformationMatrix(),
                                             sizeof(glm::mat4), 0);

                mesh.Enable();
                Application::GetGraphicsContextUnsafe()->DrawIndexed(mesh.GetIndexCount());
            }
        }
    }
} // namespace rl