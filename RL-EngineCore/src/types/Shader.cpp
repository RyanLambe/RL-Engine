#include "../../include/types/Shader.h"

Shader::Shader(ID3D11Device* device, ID3D11DeviceContext* context) {
	

	//pixel shader
	Debug::logErrorCode(D3DReadFileToBlob(L"../RL-EngineCore/PixelShader.cso", blob.Create()));
	Debug::logErrorCode(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixelShader.Create()));
	context->PSSetShader(pixelShader.Get(), 0, 0);

	//vertex shader
	Debug::logErrorCode(D3DReadFileToBlob(L"../RL-EngineCore/VertexShader.cso", blob.Create()));
	Debug::logErrorCode(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertexShader.Create()));
	context->VSSetShader(vertexShader.Get(), 0, 0);

	//input Layout
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NormalVS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	Debug::logErrorCode(device->CreateInputLayout(ied, sizeof(ied)/sizeof(D3D11_INPUT_ELEMENT_DESC), blob->GetBufferPointer(), blob->GetBufferSize(), inputLayout.Create()));
	context->IASetInputLayout(inputLayout.Get());
}