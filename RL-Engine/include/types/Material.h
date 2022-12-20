#pragma once

#include <wrl.h>
#include <d3d11.h>
#include "Texture.h"

class Material {
public:
	struct MaterialInfo {
		struct {
			float r;
			float g;
			float b;
			float a;
		} color;

		std::string textureName;
	};

public:

	Material();
	void Update(ID3D11Device* device, ID3D11DeviceContext* context);
	void Refresh();

	MaterialInfo settings;

	Texture texture;

private:
	bool set = false;

	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer;
};