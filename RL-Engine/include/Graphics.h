#pragma once
#include <d3d11.h>

class Graphics
{
public:
	~Graphics();
	
	void Start(HWND hwnd);
	void EndFrame();

private:
	ID3D11Device* device = nullptr;
	IDXGISwapChain* swap = nullptr;
	ID3D11DeviceContext* context = nullptr;
};

