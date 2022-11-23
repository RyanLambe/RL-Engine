#include "../include/Graphics.h"
#include "../include/CustomException.h"

#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

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
}

void Graphics::EndFrame()
{
	HRESULT hr;
	if (FAILED(hr = swap->Present(0, 0))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			throw GfxExcept(device->GetDeviceRemovedReason());
		else
			GfxThrowFailed(hr);
	}

	float background_colour[4] = { 255.0f/255.0f, 64.0f/255.0f, 0, 1.0f };
	context->ClearRenderTargetView(target.Get(), background_colour);
	context->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

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

void Graphics::SetShaders() {
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	D3DReadFileToBlob(L"PixelShader.cso", &blob);
	device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
	context->PSSetShader(pixelShader.Get(), 0, 0);

	D3DReadFileToBlob(L"VertexShader.cso", &blob);
	device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);
	context->VSSetShader(vertexShader.Get(), 0, 0);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	device->CreateInputLayout(ied, (UINT)std::size(ied), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);
	context->IASetInputLayout(inputLayout.Get());
}

void Graphics::DrawTriangle(float angle, float x, float y) {

	struct Vertex {
		float x;
		float y;
		float z;
	};

	Vertex verts[] = {
		{-1, -1, -1},
		{1, -1, -1},
		{-1, 1, -1},
		{1, 1, -1},
		{-1, -1, 1},
		{1, -1, 1},
		{-1, 1, 1},
		{1, 1, 1}
	};

	unsigned int indices[] = {
		0, 2, 1,  2, 3, 1,
		1, 3, 5,  3, 7, 5,
		2, 6, 3,  3, 6, 7,
		4, 5, 7,  4, 7, 6,
		0, 4, 2,  2, 4, 6,
		0, 1, 4,  1, 5, 4
	};

	// create buffers
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;

	CreateBuffer(verts, sizeof(verts), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0, &vertexBuffer);
	CreateBuffer(indices, sizeof(indices), D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_DEFAULT, 0, &indexBuffer);

	// set buffers
	UINT offset = 0;
	UINT stride = sizeof(Vertex);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	//create constant buffer
	struct ConstantBuffer {
		DirectX::XMMATRIX transform;
	};

	ConstantBuffer cb = {
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixRotationZ(angle) *
				DirectX::XMMatrixRotationX(angle)*
				DirectX::XMMatrixTranslation(x, y, 9) *
				DirectX::XMMatrixPerspectiveLH(1, 720.0f / 1280.0f, 0.5f, 10)
			)
		}
	};

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

	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer;
	CreateBuffer(&cb, sizeof(cb), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, &constBuffer);
	context->VSSetConstantBuffers(0, 1, constBuffer.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer2;
	CreateBuffer(&cb2, sizeof(cb2), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DEFAULT, 0, &constBuffer2);
	context->PSSetConstantBuffers(0, 1, constBuffer2.GetAddressOf());
	
	SetShaders();

	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	//add 
	context->DrawIndexed(sizeof(indices) / sizeof(int), 0, 0);
}