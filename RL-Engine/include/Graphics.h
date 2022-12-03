#pragma once

#include <wrl.h>

#include "InfoException.h"
#include "objects/MeshRenderer.h"

class Graphics
{
public:
	void Start(HWND hwnd);
	void EndFrame();
	void Draw();
	
	void setScene(Node scene);
	Node* getScene();

	//remove
	void DrawTriangle(float angle, float x, float y);
	void CreateBuffer(void* data, UINT size, UINT bindFlags, D3D11_USAGE use, UINT CpuAccess, ID3D11Buffer** buffer);
	void SetShaders();

private:

	int width;
	int height;

	Node scene;

	Microsoft::WRL::ComPtr<IDXGISwapChain> swap;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV;

public:
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	static Microsoft::WRL::ComPtr<ID3D11Device> device;
};

