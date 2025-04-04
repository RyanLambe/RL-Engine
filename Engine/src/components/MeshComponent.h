#pragma once

#include "../assets/Mesh.h"
#include "../ecs/Component.h"
#include "../graphics/IndexBuffer.h"
#include "../graphics/VertexBuffer.h"

namespace rl
{
    class MeshComponent : public rl::Component<MeshComponent>
    {
    public:
        void Enable() const;
        [[nodiscard]] uint32_t GetIndexCount() const;

        void LoadMesh(Mesh meshAsset);

    private:
        std::shared_ptr<VertexBuffer> vertexBuffer = nullptr;
        std::shared_ptr<IndexBuffer> indexBuffer = nullptr;
        std::shared_ptr<MeshData> meshData;
    };
}
