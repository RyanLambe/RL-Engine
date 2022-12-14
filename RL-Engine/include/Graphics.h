#pragma once

#include <wrl.h>
#include <vector>

#include "InfoException.h"
#include "objects/MeshRenderer.h"
#include "objects/Entity.h"

class Graphics
{
public:
	void Start(HWND hwnd);
	void EndFrame();
	void Draw();

	void createMesh(Entity* parent);

private:

	int width;
	int height;

	std::vector<MeshRenderer> renderers;

	Microsoft::WRL::ComPtr<IDXGISwapChain> swap;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
};

