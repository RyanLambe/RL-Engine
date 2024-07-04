#pragma once

#include "../../graphics/GraphicsContext.h"

namespace rl
{
    class VKContext : public GraphicsContext
    {
    public:
        VKContext(const GraphicsContext&) = delete;
        VKContext() = delete;
        explicit VKContext(Window* window);

        void DrawIndexed(uint32_t size) const noexcept override;

        void Present() const override;

        [[nodiscard]] void* GetDXDevice() const override;
        [[nodiscard]] void* GetDXContext() const override;

    private:
    };
}
