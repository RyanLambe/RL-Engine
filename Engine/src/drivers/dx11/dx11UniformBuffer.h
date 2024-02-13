#pragma once

#include "dx11.h"

#include "../../graphics/UniformBuffer.h"

namespace rl{
    class DX11UniformBuffer : public UniformBuffer {
    public:

        DX11UniformBuffer(uint32_t size, ShaderType shaderType, uint32_t binding);

        void SetData(const void *data, uint32_t size, uint32_t offset) override;

    private:
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer = Microsoft::WRL::ComPtr<ID3D11Buffer>();
        ShaderType shaderType;
        uint32_t binding;
    };
}
