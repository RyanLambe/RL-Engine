#pragma once

#include "../../graphics/VertexBuffer.h"
#include "VKContext.h"

namespace rl
{
    class VKVertexBuffer : public VertexBuffer
    {
    public:
        VKVertexBuffer() = delete;
        VKVertexBuffer(const std::vector<Vertex> &data, bool dynamic, const std::weak_ptr<VKContext> &contextPtr);

        void Enable() override;

        void Set(const std::vector<Vertex> &data) override;

    private:
    };
} // namespace rl
