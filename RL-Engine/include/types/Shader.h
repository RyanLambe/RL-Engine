#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

class Shader {
public:
	Shader(ID3D11Device* device, ID3D11DeviceContext* context);

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
};