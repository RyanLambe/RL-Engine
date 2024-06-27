#pragma once

#include "../ecs/Component.h"
#include "../graphics/IndexBuffer.h"
#include "../graphics/VertexBuffer.h"

namespace rl
{
    class MeshComponent : public Component<MeshComponent>
    {
    public:
        void Enable() const;
        uint32_t GetIndexCount() const;

        // todo: replace with some sort of asset system
        void LoadMesh(const std::string& fileName);

    private:
        std::shared_ptr<VertexBuffer> vertexBuffer = nullptr;
        std::shared_ptr<IndexBuffer> indexBuffer = nullptr;
        uint32_t indexCount = 0;
    };
} // namespace rl
