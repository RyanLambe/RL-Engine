#include "dx11Shader.h"

using namespace rl;

DX11Shader::DX11Shader(const std::string& vertexShaderPath, const std::string& pixelShaderPath,
                       const std::weak_ptr<DX11Context>& contextPtr) :
    contextPtr(contextPtr)
{
    const std::wstring pixelPath(pixelShaderPath.begin(), pixelShaderPath.end());
    const std::wstring vertexPath(vertexShaderPath.begin(), vertexShaderPath.end());

    auto context = contextPtr.lock();
    if (!context)
    {
        RL_THROW_EXCEPTION("Cannot access Context");
    }

    // pixel shader
    DX_LOG_ERROR(D3DReadFileToBlob(pixelPath.c_str(), &blob));
    DX_LOG_ERROR(context->GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr,
                                                         &pixelShader));

    // vertex shader
    DX_LOG_ERROR(D3DReadFileToBlob(vertexPath.c_str(), &blob));
    DX_LOG_ERROR(context->GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr,
                                                          &vertexShader));

    // input Layout
    D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TexCoord", 0,    DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NormalVS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    DX_LOG_ERROR(context->GetDevice()->CreateInputLayout(
        (D3D11_INPUT_ELEMENT_DESC*)ied, sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC), blob->GetBufferPointer(),
        blob->GetBufferSize(), &inputLayout));
}

void DX11Shader::Enable()
{
    auto context = contextPtr.lock();
    if (!context)
    {
        RL_THROW_EXCEPTION("Cannot access Context");
    }

    context->GetContext()->PSSetShader(pixelShader.Get(), nullptr, 0);
    context->GetContext()->VSSetShader(vertexShader.Get(), nullptr, 0);
    context->GetContext()->IASetInputLayout(inputLayout.Get());
}
