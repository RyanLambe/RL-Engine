#include "Material.h"

using namespace rl;

Material::Material() {
	texture.Set(settings.textureName);
}

void Material::Update(ID3D11Device* device, ID3D11DeviceContext* context) {

	//if the material has already been setup dont do it again
	if (set) {
		texture.Update(device, context);
		context->PSSetConstantBuffers(0, 1, constBuffer.GetAddressOf());
		return;
	}

	//set texture
	texture.Set(settings.textureName);
	texture.Update(device, context);
	settings.texId = texture.getId();

	//setup
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = 32+16;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &(settings);
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	//create constant buffer
	//todo: no directx code here
    //Debug::logErrorCode(device->CreateBuffer(&bufferDesc, &initData, &constBuffer));
	context->PSSetConstantBuffers(0, 1, constBuffer.GetAddressOf());

	set = true;
}

void Material::SetTexture(std::string textureName)
{
	settings.textureName = textureName;
	Refresh();
}

void Material::Refresh() {
	set = false;
}

Material& Material::operator=(const Material& other) {
	this->settings = other.settings;
	set = false;
	return *this;
}
