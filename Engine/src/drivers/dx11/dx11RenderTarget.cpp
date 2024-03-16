#include "dx11RenderTarget.h"

#include "dx11Context.h"

using namespace rl;

unsigned long long data = -1;

DX11RenderTarget::DX11RenderTarget(bool useSwapChain) : useSwapChain(useSwapChain)
{
	Resize(DX11Context::GetWindowWidth(), DX11Context::GetWindowHeight());
}

void DX11RenderTarget::Enable() noexcept
{
    DX11Context::GetContext()->OMSetRenderTargets(1, target.GetAddressOf(), DSV.Get());

    D3D11_VIEWPORT vp;
    vp.Width = (float)width;
    vp.Height = (float)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    DX11Context::GetContext()->RSSetViewports( 1, &vp );
}

void DX11RenderTarget::Clear() noexcept
{
	if(useSwapChain)
		if(width != DX11Context::GetWindowWidth() || height != DX11Context::GetWindowHeight())
			Resize(DX11Context::GetWindowWidth(), DX11Context::GetWindowHeight());

	DX11Context::GetContext()->ClearRenderTargetView(target.Get(), &clearColor[0]);
	DX11Context::GetContext()->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void DX11RenderTarget::SetClearColor(const glm::vec4& value) noexcept
{
	clearColor = value;
}

void DX11RenderTarget::Resize(uint32_t width, uint32_t height) noexcept
{
	this->width = width;
	this->height = height;

    if(useSwapChain){

        DX11Context::GetContext()->OMSetRenderTargets(0, nullptr, nullptr);
        target.Reset();
        resView.Reset();

        DX_LOG_ERROR(DX11Context::GetSwap()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));
        DX_LOG_ERROR(DX11Context::GetSwap()->GetBuffer(0, __uuidof(ID3D11Texture2D), &renderTexture));
    }
    else{
        DX11Context::GetContext()->OMSetRenderTargets(0, nullptr, nullptr);
        target.Reset();
        resView.Reset();

        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = width;
        textureDesc.Height = height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;
        DX_LOG_ERROR(DX11Context::GetDevice()->CreateTexture2D(&textureDesc, nullptr, &renderTexture));
    }

    DX_LOG_ERROR(DX11Context::GetDevice()->CreateRenderTargetView(renderTexture.Get(), nullptr, &target));
    DX_LOG_ERROR(DX11Context::GetDevice()->CreateShaderResourceView(renderTexture.Get(), nullptr, &resView));
    renderTexture.Reset();

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
}

void *DX11RenderTarget::GetTexture() noexcept {
    return resView.Get();
}

