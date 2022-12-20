#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <string>
#include <vector>

//external
//https://lodev.org/lodepng/
#include "../../External/LodePng/lodepng.h"

class Texture {
public:
	void Set(ID3D11Device* device, std::string fileName);
	void Update(ID3D11DeviceContext* context);

private:

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texView;

};