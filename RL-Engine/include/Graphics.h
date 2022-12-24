#pragma once

#include <wrl.h>
#include <vector>

#include "InfoException.h"
#include "objects/MeshRenderer.h"
#include "objects/PointLight.h"
#include "objects/DirectionalLight.h"

#define MaxLights 4

class Graphics
{
public:
	void Start(HWND hwnd);
	void EndFrame();
	void Draw();

	MeshRenderer* createMesh(Entity* parent);
	PointLight* createPointLight(Entity* parent);
	void setDirectionalLight(DirectionalLight* light);

private:

	void updateLightData();
	void updateLightBuffer();
	void updateCameraBuffer(DirectX::XMMATRIX mat);

private:

	int width;
	int height;

	//meshs to be rendered
	std::vector<MeshRenderer> renderers;

	//lights
	//const static int maxLights = 4;
	struct LightData {

		DirectX::XMVECTOR positions[1 + MaxLights];//1 dir + max point

		struct DirectionalLightDetails {
			float r;
			float g;
			float b;
			float space; // space to align floats by 4
		}dirDetails;

		struct PointLightDetails {
			float r;
			float g;
			float b;
			float power;
			float range;
			float space1, space2, space3; // spaces to align floats by 4
		}pntDetails[MaxLights];

	} lightData;

	std::vector<PointLight> pointLights;
	DirectionalLight* directionalLight;


	//rendering
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV;

	//accessing directX
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	//textures
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
};

