#include "../../include/types/Material.h"

Material::Material() {
}

void Material::Update(ID3D11Device* device, ID3D11DeviceContext* context) {
	//???
	//if the material has already been setup dont do it again
	if (set)
		return;

	//setup
	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer;

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(settings);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &settings;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	//create constant buffer
	device->CreateBuffer(&bufferDesc, &initData, &constBuffer);
	context->PSSetConstantBuffers(0, 1, constBuffer.GetAddressOf());

}

void Material::Refresh() {
	set = false;
}
