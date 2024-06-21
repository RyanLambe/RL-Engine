#pragma once

#include "VKContext.h"

#include "../../graphics/IndexBuffer.h"

namespace rl {
    class VKIndexBuffer : public IndexBuffer {
    public:
        VKIndexBuffer() = delete;
        VKIndexBuffer(const std::vector<uint32_t>& data, bool dynamic, const std::weak_ptr<VKContext>& contextPtr);

        void Enable() override;

        void Set(const std::vector<uint32_t>& data) override;

    private:

    };
}
