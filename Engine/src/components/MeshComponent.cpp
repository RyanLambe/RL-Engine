#include "MeshComponent.h"

#include "../core/Application.h"

void rl::MeshComponent::Enable() const
{
    if (vertexBuffer == nullptr || indexBuffer == nullptr)
        return;

    vertexBuffer->Enable();
    indexBuffer->Enable();
}

uint32_t rl::MeshComponent::GetIndexCount() const
{
    if (const auto& m = mesh.lock())
        return m->GetIndexCount();
    RL_LOG_ERROR("Missing Mesh");
    return 0;
}

void rl::MeshComponent::LoadMesh(const std::weak_ptr<Mesh>& meshAsset)
{
    const auto m = meshAsset.lock();
    if (!m)
    {
        RL_LOG_ERROR("The input mesh is null");
        return;
    }

    mesh = meshAsset;
    vertexBuffer = VertexBuffer::Create(m->GetVertices(), false, Application::GetGraphicsContextPtr());
    indexBuffer = IndexBuffer::Create(m->GetIndices(), false, Application::GetGraphicsContextPtr());
}