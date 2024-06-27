#pragma once

#include "../../graphics/Shader.h"
#include "DX11.h"
#include "DX11Context.h"

namespace rl
{
    class DX11Shader : public Shader
    {
    public:
        DX11Shader(const std::string &vertexShaderPath, const std::string &pixelShaderPath,
                   const std::weak_ptr<DX11Context> &contextPtr);

        void Enable() override;

    private:
        std::weak_ptr<DX11Context> contextPtr;

        Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = Microsoft::WRL::ComPtr<ID3D11VertexShader>();
        Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = Microsoft::WRL::ComPtr<ID3D11PixelShader>();
        Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = Microsoft::WRL::ComPtr<ID3D11InputLayout>();
        Microsoft::WRL::ComPtr<ID3DBlob> blob = Microsoft::WRL::ComPtr<ID3DBlob>();
    };
} // namespace rl
