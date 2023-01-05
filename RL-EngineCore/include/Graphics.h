#pragma once

#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>

#include "Debug.h"
#include "types/SmartPtr.h"
#include "objects/MeshRenderer.h"
#include "objects/PointLight.h"
#include "objects/DirectionalLight.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#define MaxTotalLights 128
#define MaxLights 8

class Graphics
{
public:
	void Start(HWND hwnd, int width, int height);
	void EndFrame();
	void Draw();

	MeshRenderer* createMesh(Entity* parent);
	PointLight* createPointLight(Entity* parent);
	void setDirectionalLight(DirectionalLight* light);

	//[0] = top, [1] = bottom
	//[2] = left, [3] = right
	//[4] = front, [5] = back
	void setSkybox(std::string sides[6]);
	void setAmbientStrength(float strength);
	void setBackgroundColour(float colour[4]);

	static int getWidth();
	static int getHeight();

	void updateDimensions(int width, int height);
	void setFullscreen(bool fullscreen);

private:

	void updateLightData();
	void updatePixelShader();
	void updateVertexShader();

private:

	static int width;
	static int height;

	//constant buffers
	//vertex shader
	bool vsBufferCreated = false;
	SmartPtr<ID3D11Buffer> vsBuffer;
	struct VSBufferData {
		DirectX::XMMATRIX camMatrix;
		DirectX::XMVECTOR lightPos[MaxTotalLights + 1];
	} vsBufferData;

	//pixel shader
	bool psBufferCreated = false;
	SmartPtr<ID3D11Buffer> psBuffer;
	struct PSBufferData {

		struct DirectionalLightDetails {
			float r;
			float g;
			float b;
			float space; // space to align floats by 4
		}dirLightDetails;

		struct PointLightDetails {
			float r;
			float g;
			float b;
			float power;
			float range;
			float space1, space2, space3; // spaces to align floats by 4
		}pntLightDetails[MaxLights];

		struct AmbientLight {
			float r;
			float g;
			float b;
			float space; // space to align floats by 4
		}ambientLight;

	} psBufferData;

	//meshs to be rendered
	std::vector<MeshRenderer> renderers;
	 
	//lights
	float ambientStrength = 0.25f;
	bool skyboxEnabled = false;
	float backgroundColour[4] = {1, 155.0f/255.0f, 0, 1};

	std::vector<PointLight> pointLights;
	DirectionalLight* directionalLight;

	//skybox
	Entity skybox;

	//rendering
	SmartPtr<IDXGISwapChain> swap;
	SmartPtr<ID3D11RenderTargetView> target;
	SmartPtr<ID3D11DepthStencilView> DSV;

	//accessing directX
	SmartPtr<ID3D11DeviceContext> context;
	SmartPtr<ID3D11Device> device;

	//textures
	SmartPtr<ID3D11SamplerState> sampler;
};

