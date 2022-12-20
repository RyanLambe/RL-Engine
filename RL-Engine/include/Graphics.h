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

		struct LightPos {
			float x;
			float y;
			float z;
		}positions[1 + MaxLights];//1 dir + max point

		struct LightDetails {
			float r;
			float g;
			float b;
		}details[1 + MaxLights];

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

