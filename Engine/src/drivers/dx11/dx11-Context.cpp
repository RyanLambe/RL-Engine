#include "dx11-Context.h"

#include <exception>

#include "../../Debug.h"
#include "../../types/Shader.h"

using namespace rl::impl;

#define checkError(code) if(FAILED(code)) throw std::runtime_error(Debug::TranslateHResult(code).c_str())

DX11Context* rl::impl::DX11Context::mainContext = nullptr;

DX11Context::DX11Context(HWND hwnd, uint32_t width, uint32_t height) {
	
	if (mainContext) {
		// critical error
		return;
	}
	mainContext = this;

	this->width = width;
	this->height = height;

	//create device, context, and swap chain
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	checkError(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swap, &device, nullptr, &context));

	//set viewport size
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);

	//set topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//setup sampler
	D3D11_SAMPLER_DESC sampleDesc = {};
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	checkError(device->CreateSamplerState(&sampleDesc, &sampler));
	context->PSSetSamplers(0, 1, sampler.GetAddressOf());

	rl::Shader shader = rl::Shader();
	shader.Start(device.Get(), context.Get());\
}

void DX11Context::DrawIndexed(uint32_t size) const noexcept
{
	context->DrawIndexed((UINT)size, 0, 0);
}

void DX11Context::Present() const noexcept
{
	HRESULT hr;
	context->Flush();
	if (FAILED(hr = swap->Present(vsync, 0))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			checkError(device->GetDeviceRemovedReason());
		}
		else
		{
			Debug::logErrorCode(hr);
		}
	}
}

void rl::impl::DX11Context::EnableTransparency(bool enable) const noexcept
{
	D3D11_BLEND_DESC BlendStateDescription = CD3D11_BLEND_DESC{ CD3D11_DEFAULT{} };
	ID3D11BlendState* blend;

	BlendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	BlendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendStateDescription.AlphaToCoverageEnable = true;
	BlendStateDescription.IndependentBlendEnable = false;

	device->CreateBlendState(&BlendStateDescription, &blend);

	constexpr float blendFactor[] = { 1, 1, 1, 1 };
	if(enable)
	{
		context->OMSetBlendState(blend, blendFactor, 0xffffffff);
	}
	else
	{
		context->OMSetBlendState(blend, blendFactor, 0); // does this work???
	}
}

void rl::impl::DX11Context::EnableDepth(bool enable) const noexcept
{
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};

	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthState;
	checkError(device->CreateDepthStencilState(&dsDesc, &depthState));
	context->OMSetDepthStencilState(depthState.Get(), 1);
	depthState.Reset();
}

ID3D11DeviceContext* DX11Context::GetContext()
{
	return mainContext->context.Get();
}

ID3D11Device* DX11Context::GetDevice()
{
	return mainContext->device.Get();
}

IDXGISwapChain* DX11Context::GetSwap()
{
	return mainContext->swap.Get();
}

uint32_t rl::impl::DX11Context::GetWindowWidth()
{
	return mainContext->width;
}

uint32_t rl::impl::DX11Context::GetWindowHeight()
{
	return mainContext->height;
}
