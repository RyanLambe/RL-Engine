#include "dx11Shader.h"

#include "dx11Context.h"

using namespace rl;

DX11Shader::DX11Shader(const std::string& vertexShaderPath, const std::string& pixelShaderPath) {

    const std::wstring pixelPath(pixelShaderPath.begin(), pixelShaderPath.end());
    const std::wstring vertexPath(vertexShaderPath.begin(), vertexShaderPath.end());

    //pixel shader
    DX_LOG_ERROR(D3DReadFileToBlob(pixelPath.c_str(), &blob));
    DX_LOG_ERROR(DX11Context::GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader));

    //vertex shader
    DX_LOG_ERROR(D3DReadFileToBlob(vertexPath.c_str(), &blob));
    DX_LOG_ERROR(DX11Context::GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader));

    //input Layout
    D3D11_INPUT_ELEMENT_DESC ied[] = {
            {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NormalVS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    DX_LOG_ERROR(DX11Context::GetDevice()->CreateInputLayout(ied, sizeof(ied)/sizeof(D3D11_INPUT_ELEMENT_DESC), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout));
}

void DX11Shader::Enable() {

    DX11Context::GetContext()->PSSetShader(pixelShader.Get(), 0, 0);
    DX11Context::GetContext()->VSSetShader(vertexShader.Get(), 0, 0);
    DX11Context::GetContext()->IASetInputLayout(inputLayout.Get());
}
