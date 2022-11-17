#pragma once

#include <wrl.h>

#include "InfoException.h"

#include <d3dcompiler.h>

class Graphics
{
public:
	void Start(HWND hwnd);
	void EndFrame();
	void DrawTriangle();

private:

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target;
};

