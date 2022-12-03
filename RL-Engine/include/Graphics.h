#pragma once

#include <wrl.h>
#include <vector>

#include "InfoException.h"
#include "objects/MeshRenderer.h"

class Graphics
{
public:
	void Start(HWND hwnd);
	void EndFrame();
	void Draw();

	void createMesh(Entity* parent);

	//remove
	//void DrawTriangle(float angle, float x, float y);
	void CreateBuffer(void* data, UINT size, UINT bindFlags, D3D11_USAGE use, UINT CpuAccess, ID3D11Buffer** buffer);
	//void SetShaders();

private:

	int width;
	int height;

	std::vector<MeshRenderer> renderers;

	Microsoft::WRL::ComPtr<IDXGISwapChain> swap;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV;

private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
};

