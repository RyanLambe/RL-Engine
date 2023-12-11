#include "Texture.h"

int Core::Texture::nextId = 0;
std::map<std::string, int> Core::Texture::idMap;

Core::Texture::Texture() {
}

void Core::Texture::Set(std::string fileName) {
	name = fileName;
}

void Core::Texture::Update(ID3D11Device* device, ID3D11DeviceContext* context) {
	
	//if correct return
	if (idMap.count(name) == 1) 
		return;

	//get texture
	std::vector<unsigned char> image;
	unsigned int height, width;
	lodepng::decode(image, width, height, name.c_str());

	//get average colour
	int count = 0;
	for (int i = 0; i < image.size(); i++) {
		if (count == 0) {
			avColour[0] += image[i];
			count++;
		}
		else if (count == 1) {
			avColour[1] += image[i];
			count++;
		}
		else if (count == 2) {
			avColour[2] += image[i];
			count++;
		}
		else if (count == 3)
			count = 0;
	}

	avColour[0] /= (image.size() / 4);
	avColour[1] /= (image.size() / 4);
	avColour[2] /= (image.size() / 4);

	avColour[0] /= 255;
	avColour[1] /= 255;
	avColour[2] /= 255;

	//create texture
	D3D11_TEXTURE2D_DESC imgDesc = {};
	imgDesc.Width = width;
	imgDesc.Height = height;
	imgDesc.MipLevels = 1;
	imgDesc.ArraySize = 1;
	imgDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	imgDesc.SampleDesc.Count = 1;
	imgDesc.SampleDesc.Quality = 0;
	imgDesc.Usage = D3D11_USAGE_IMMUTABLE;
	imgDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	imgDesc.CPUAccessFlags = 0;
	imgDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = image.data();
	data.SysMemPitch = width * 4;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	Debug::logErrorCode(device->CreateTexture2D(&imgDesc, &data, &texture2D));

	//create resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC resDesc = {};
	resDesc.Format = imgDesc.Format;
	resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resDesc.Texture2D.MostDetailedMip = 0;
	resDesc.Texture2D.MipLevels = 1;

	Debug::logErrorCode(device->CreateShaderResourceView(texture2D.Get(), &resDesc, &texView));

	if (idMap.count(name) != 1) {
		idMap.insert(std::pair<std::string, int>(name, nextId));
		nextId++;
	}

	context->PSSetShaderResources(idMap.at(name), 1, texView.GetAddressOf());
}

int Core::Texture::getId()
{
	return idMap.at(name);
}

float* Core::Texture::getAverage()
{
	return avColour;
}