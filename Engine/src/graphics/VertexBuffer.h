#pragma once

#include <memory>
#include <vector>

#include "../types/Vertex.h"
#include "GraphicsContext.h"

namespace rl
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        static std::shared_ptr<VertexBuffer> Create(const std::vector<Vertex>& data, bool dynamic,
                                                    const std::weak_ptr<GraphicsContext>& context);

        virtual void Enable() = 0;

        virtual void Set(const std::vector<Vertex>& data) = 0;
    };
} // namespace rl