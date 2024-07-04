#pragma once

#include "../../graphics/UniformBuffer.h"
#include "DX11.h"
#include "DX11Context.h"

namespace rl
{
    class DX11UniformBuffer : public UniformBuffer
    {
    public:
        DX11UniformBuffer(uint32_t size, ShaderType shaderType, uint32_t binding,
                          const std::weak_ptr<DX11Context>& contextPtr);

        void SetData(const void* data, uint32_t size, uint32_t offset) override;

    private:
        std::weak_ptr<DX11Context> contextPtr;
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer = Microsoft::WRL::ComPtr<ID3D11Buffer>();
        ShaderType shaderType;
        uint32_t binding;
    };
}
