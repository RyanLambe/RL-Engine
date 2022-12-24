#include "../../include/types/Material.h"

Material::Material() {
	settings.color = { 1, 1, 1, 1 };
	settings.textureName = "assets/default.png";
	settings.smoothness = 0.5f;
	settings.reflectivity = 0.25f;
}

void Material::Update(ID3D11Device* device, ID3D11DeviceContext* context) {
	
	//update texture
	texture.Update(context);

	//if the material has already been setup dont do it again
	if (set) {
		context->PSSetConstantBuffers(0, 1, constBuffer.GetAddressOf());
		return;
	}

	//setup
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(settings.color) + 16;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &(settings);
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	//create constant buffer
	device->CreateBuffer(&bufferDesc, &initData, &constBuffer);
	context->PSSetConstantBuffers(0, 1, constBuffer.GetAddressOf());

	//set texture
	texture.Set(device, settings.textureName);

	set = true;
}

void Material::Refresh() {
	set = false;
}
