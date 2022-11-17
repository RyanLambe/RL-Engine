#include "../include/Graphics.h"
#include "../include/CustomException.h"

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

	Microsoft::WRL::ComPtr<ID3D11Texture2D> frameBuffer;
	swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&frameBuffer);
	device->CreateRenderTargetView(frameBuffer.Get(), 0, &target);
	frameBuffer.Reset();
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

	float background_colour[4] = { 0, 0, 1, 1.0f };
	context->ClearRenderTargetView(target.Get(), background_colour);
}

void Graphics::DrawTriangle() {

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;

	struct Vertex {
		float x;
		float y;
	};

	Vertex verts[] = {
		{0.0f, 0.5f },
		{0.5f, -0.5f},
		{-0.5f, -0.5f}
	};

	unsigned int indices[] = { 0, 2, 1 };

	D3D11_BUFFER_DESC ibufferDesc;
	ibufferDesc.Usage = D3D11_USAGE_DEFAULT;
	ibufferDesc.ByteWidth = sizeof(unsigned int) * 3;
	ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibufferDesc.CPUAccessFlags = 0;
	ibufferDesc.MiscFlags = 0;

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(Vertex) * 3;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = verts;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	D3D11_SUBRESOURCE_DATA IinitData;
	IinitData.pSysMem = indices;
	IinitData.SysMemPitch = 0;
	IinitData.SysMemSlicePitch = 0;

	device->CreateBuffer(&ibufferDesc, &IinitData, &indexBuffer);
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);


	device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

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
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	device->CreateInputLayout(ied, (UINT)std::size(ied), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);
	context->IASetInputLayout(inputLayout.Get());


	context->OMSetRenderTargets(1, target.GetAddressOf(), nullptr);

	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	context->Draw(3, 0);
}