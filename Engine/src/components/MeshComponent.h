#pragma once

#include "../ecs/Component.h"
#include "../graphics/VertexBuffer.h"
#include "../graphics/IndexBuffer.h"

namespace rl {
    class MeshComponent : public Component<MeshComponent> {
    public:

        void Enable();
        size_t GetIndexCount();

        // todo: replace with some sort of asset system
        void LoadMesh(const std::string& fileName);

    private:
        std::shared_ptr<VertexBuffer> vertexBuffer = nullptr;
        std::shared_ptr<IndexBuffer> indexBuffer = nullptr;
        size_t indexCount = 0;
    };
}
