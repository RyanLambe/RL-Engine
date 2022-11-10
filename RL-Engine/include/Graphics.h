#pragma once
#include <d3d11.h>
#include <wrl.h>

class Graphics
{
public:
	void Start(HWND hwnd);
	void EndFrame();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
};

