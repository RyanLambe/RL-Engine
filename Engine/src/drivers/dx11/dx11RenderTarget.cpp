#include "dx11RenderTarget.h"

#include "dx11Context.h"

using namespace rl;

DX11RenderTarget::DX11RenderTarget()
{
	windowSize = true;
	depthEnabled = false;

	width = DX11Context::GetWindowWidth();
	height = DX11Context::GetWindowHeight();

	// create render target
	DX11Context::GetSwap()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&texture);
	DX11Context::GetDevice()->CreateRenderTargetView(texture.Get(), 0, &target);
	texture.Reset();
}

void DX11RenderTarget::Enable() const noexcept
{
	
}

void DX11RenderTarget::Clear() noexcept
{
	if(windowSize)
		if(width != DX11Context::GetWindowWidth() || height != DX11Context::GetWindowHeight())
			Resize(DX11Context::GetWindowWidth(), DX11Context::GetWindowHeight());

	DX11Context::GetContext()->ClearRenderTargetView(target.Get(), &clearColor[0]);
	DX11Context::GetContext()->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void DX11RenderTarget::SetClearColor(const glm::vec4& value) noexcept
{
	clearColor = value;
}

void DX11RenderTarget::EnableDepthTest(bool enable) noexcept
{
	depthEnabled = enable;
	Resize(width, height);
}

void DX11RenderTarget::Resize(uint32_t width, uint32_t height) noexcept
{
	this->width = width;
	this->height = height;

	DXGI_MODE_DESC dxgiDesc = {};
	dxgiDesc.Width = width;
	dxgiDesc.Height = height;
	dxgiDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	dxgiDesc.RefreshRate.Numerator = 1000;
	dxgiDesc.RefreshRate.Denominator = 1;
	dxgiDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	dxgiDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    DX_LOG_ERROR(DX11Context::GetSwap()->ResizeTarget(&dxgiDesc));

	// resize depth
	if (depthEnabled)
	{
		// get depth texture
		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;
		D3D11_TEXTURE2D_DESC depthDesc = {};
		depthDesc.Width = width;
		depthDesc.Height = height;
		depthDesc.MipLevels = 1;
		depthDesc.ArraySize = 1;
		depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthDesc.SampleDesc.Count = 1;
		depthDesc.SampleDesc.Quality = 0;
		depthDesc.Usage = D3D11_USAGE_DEFAULT;
		depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        DX_LOG_ERROR(DX11Context::GetDevice()->CreateTexture2D(&depthDesc, nullptr, &depthTexture));

		//set depth texture
		D3D11_DEPTH_STENCIL_VIEW_DESC DSVdesc = {};
		DSVdesc.Format = DXGI_FORMAT_D32_FLOAT;
		DSVdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		DSVdesc.Texture2D.MipSlice = 0;
        DX_LOG_ERROR(DX11Context::GetDevice()->CreateDepthStencilView(depthTexture.Get(), &DSVdesc, &DSV));

		DX11Context::GetContext()->OMSetRenderTargets(1, target.GetAddressOf(), DSV.Get());
	}
}

