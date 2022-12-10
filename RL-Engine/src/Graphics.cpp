#include "../include/Graphics.h"

#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

//update
void Graphics::Start(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};

	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	
	GfxThrowFailed(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swap, &device, nullptr, &context));

	// get render target
	Microsoft::WRL::ComPtr<ID3D11Texture2D> frameBuffer;
	swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&frameBuffer);
	device->CreateRenderTargetView(frameBuffer.Get(), 0, &target);
	
	// render closer object on top
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthState;
	device->CreateDepthStencilState(&dsDesc, &depthState);
	context->OMSetDepthStencilState(depthState.Get(), 1);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;
	D3D11_TEXTURE2D_DESC depthDesc = {};
	depthDesc.Width = 1280;
	depthDesc.Height = 720;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	device->CreateTexture2D(&depthDesc, nullptr, &depthTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC DSVdesc = {};
	DSVdesc.Format = DXGI_FORMAT_D32_FLOAT;
	DSVdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DSVdesc.Texture2D.MipSlice = 0;
	device->CreateDepthStencilView(depthTexture.Get(), &DSVdesc, &DSV);

	context->OMSetRenderTargets(1, target.GetAddressOf(), DSV.Get());

	//set viewport size
	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);

	//set topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

//update
void Graphics::EndFrame()
{
	HRESULT hr;
	if (FAILED(hr = swap->Present(0, 0))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			throw GfxExcept(Graphics::device->GetDeviceRemovedReason());
		else
			GfxThrowFailed(hr);
	}

	float background_colour[4] = { 255.0f/255.0f, 64.0f/255.0f, 0, 1.0f };
	context->ClearRenderTargetView(target.Get(), background_colour);
	context->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void Graphics::Draw() {
	//move to shader or a material class or something
	struct ConstantBuffer2 {
		struct {
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};

	ConstantBuffer2 cb2 = {
		{
			{1, 0, 1},
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1},
			{1, 1, 0},
			{0, 1, 1}
		}
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer2;
	CreateBuffer(&cb2, sizeof(cb2), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DEFAULT, 0, &constBuffer2);
	context->PSSetConstantBuffers(0, 1, constBuffer2.GetAddressOf());


	//set shaders. move to mesh renderer
	Shader temp(device.Get(), context.Get());

	//render
	for (int i = 0; i < renderers.size(); i++) {
		renderers[i].Draw(device.Get(), context.Get());
	}
}

void Graphics::createMesh(Entity* parent) {
	renderers.emplace_back(device.Get(), context.Get(), parent);
	parent->addComponent(&renderers[renderers.size()-1]);
}

//remove
void Graphics::CreateBuffer(void* data, UINT size, UINT bindFlags, D3D11_USAGE use, UINT CpuAccess, ID3D11Buffer** buffer) {

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = use;
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = bindFlags;
	bufferDesc.CPUAccessFlags = CpuAccess;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	device->CreateBuffer(&bufferDesc, &initData, buffer);
}