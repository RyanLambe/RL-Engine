#pragma once

#include <wrl.h>
#include <d3d11.h>

class Material {
public:
	struct MaterialInfo {
		struct {
			float r;
			float g;
			float b;
			float a;
		} color;
	};

public:


	Material();
	void Update(ID3D11Device* device, ID3D11DeviceContext* context);
	void Refresh();

	MaterialInfo settings;

private:
	bool set = false;

};