#pragma once

#include "dx11.h"

#include "../../graphics/Shader.h"

namespace rl {
    class DX11Shader : public Shader {
    public:

        DX11Shader(const std::string& vertexShaderPath, const std::string& pixelShaderPath);

        void Enable() override;

    private:

        Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = Microsoft::WRL::ComPtr<ID3D11VertexShader>();
        Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = Microsoft::WRL::ComPtr<ID3D11PixelShader>();
        Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = Microsoft::WRL::ComPtr<ID3D11InputLayout>();
        Microsoft::WRL::ComPtr<ID3DBlob> blob = Microsoft::WRL::ComPtr<ID3DBlob>();

    };
}
