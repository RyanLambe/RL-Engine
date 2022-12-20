#include "../../include/types/Texture.h"

//using namespace cimg_library;

void Texture::Set(ID3D11Device* device, const std::string fileName) {

	//getTexture
	std::vector<unsigned char> image;
	unsigned int height, width;
	lodepng::decode(image, width, height, fileName.c_str());

	//create texture
	D3D11_TEXTURE2D_DESC imgDesc = {};
	imgDesc.Width = width;
	imgDesc.Height = height;
	imgDesc.MipLevels = 1;
	imgDesc.ArraySize = 1;
	imgDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	imgDesc.SampleDesc.Count = 1;
	imgDesc.SampleDesc.Quality = 0;
	imgDesc.Usage = D3D11_USAGE_DEFAULT;
	imgDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	imgDesc.CPUAccessFlags = 0;
	imgDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = image.data();
	data.SysMemPitch = width * 4;

	device->CreateTexture2D(&imgDesc, &data, &texture2D);

	//create resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC resDesc = {};
	resDesc.Format = imgDesc.Format;
	resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resDesc.Texture2D.MostDetailedMip = 0;
	resDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(texture2D.Get(), &resDesc, &texView);
}

void Texture::Update(ID3D11DeviceContext* context) {
	context->PSSetShaderResources(0, 1, texView.GetAddressOf());
}
