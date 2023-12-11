#include "Shader.h"

Core::Shader::Shader() {
}

void Core::Shader::Start(ID3D11Device* device, ID3D11DeviceContext* context) {
	
	//pixel shader
	Debug::logErrorCode(D3DReadFileToBlob(L"PixelShader.cso", &blob));
	Debug::logErrorCode(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader));
	context->PSSetShader(pixelShader.Get(), 0, 0);

	//vertex shader
	Debug::logErrorCode(D3DReadFileToBlob(L"VertexShader.cso", &blob));
	Debug::logErrorCode(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader));
	context->VSSetShader(vertexShader.Get(), 0, 0);

	//input Layout
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NormalVS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	Debug::logErrorCode(device->CreateInputLayout(ied, sizeof(ied)/sizeof(D3D11_INPUT_ELEMENT_DESC), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout));
	context->IASetInputLayout(inputLayout.Get());
}