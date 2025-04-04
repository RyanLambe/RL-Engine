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
    return meshData->GetIndexCount();
}

void rl::MeshComponent::LoadMesh(Mesh mesh)
{
    if (Application::GetAssetManager().IsAssetLoaded(mesh))
    {
        RL_LOG_ERROR("The input mesh is null");
        return;
    }

    meshData = std::static_pointer_cast<MeshData>(Application::GetAssetManager().GetAssetData(mesh));
    vertexBuffer = VertexBuffer::Create(meshData->GetVertices(), false, Application::GetGraphicsContextPtr());
    indexBuffer = IndexBuffer::Create(meshData->GetIndices(), false, Application::GetGraphicsContextPtr());
}