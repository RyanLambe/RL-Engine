#include "dx11RenderTarget.h"

#include "dx11Context.h"

using namespace rl;

unsigned long long data = -1;

DX11RenderTarget::DX11RenderTarget(const std::weak_ptr<Window>& windowPtr, const std::weak_ptr<DX11Context>& contextPtr)
: contextPtr(contextPtr), windowPtr(windowPtr)
{
    if(contextPtr.expired()){
        RL_THROW_EXCEPTION("Cannot access Context");
    }

    if(auto window = windowPtr.lock()){
        width = window->GetWidth();
        height = window->GetHeight();
        Refresh();
    }
    else{
        RL_THROW_EXCEPTION("Cannot access Window");
    }
}

DX11RenderTarget::DX11RenderTarget(uint32_t width, uint32_t height, const std::weak_ptr<DX11Context> &contextPtr)
: width(width), height(height), contextPtr(contextPtr) {
    if(contextPtr.expired()){
        RL_THROW_EXCEPTION("Cannot access Context");
    }
    Refresh();
}

void DX11RenderTarget::Enable()
{
    auto context = contextPtr.lock();
    if(!context)
        RL_THROW_EXCEPTION("Cannot access Context");

    context->GetContext()->OMSetRenderTargets(1, target.GetAddressOf(), DSV.Get());

    D3D11_VIEWPORT vp;
    vp.Width = (float)width;
    vp.Height = (float)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    context->GetContext()->RSSetViewports(1, &vp);
}

void DX11RenderTarget::Clear()
{
    auto context = contextPtr.lock();
    if(!context)
        RL_THROW_EXCEPTION("Cannot access Context");

	if(windowPtr.has_value()){
        auto window = windowPtr.value().lock();
        if(!window)
            RL_THROW_EXCEPTION("Cannot access Window");

        if(width != window->GetWidth() || height != window->GetHeight()){
            width = window->GetWidth();
            height = window->GetHeight();
            Refresh();
        }
    }

	context->GetContext()->ClearRenderTargetView(target.Get(), &clearColor[0]);
	context->GetContext()->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void DX11RenderTarget::SetClearColor(const glm::vec4& value) noexcept
{
	clearColor = value;
}

void DX11RenderTarget::Resize(uint32_t w, uint32_t h)
{
	width = w;
	height = h;

    Refresh();
}

void *DX11RenderTarget::GetTexture() noexcept {
    return resView.Get();
}

void DX11RenderTarget::Refresh() {

    auto context = contextPtr.lock();
    if(!context)
        RL_THROW_EXCEPTION("Cannot access Context");

    if(windowPtr.has_value()){
        context->GetContext()->OMSetRenderTargets(0, nullptr, nullptr);
        target.Reset();
        resView.Reset();

        DX_LOG_ERROR(context->GetSwap()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));
        DX_LOG_ERROR(context->GetSwap()->GetBuffer(0, __uuidof(ID3D11Texture2D), &renderTexture));
    }
    else{
        context->GetContext()->OMSetRenderTargets(0, nullptr, nullptr);
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
        DX_LOG_ERROR(context->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &renderTexture));
    }

    DX_LOG_ERROR(context->GetDevice()->CreateRenderTargetView(renderTexture.Get(), nullptr, &target));
    DX_LOG_ERROR(context->GetDevice()->CreateShaderResourceView(renderTexture.Get(), nullptr, &resView));
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
    DX_LOG_ERROR(context->GetDevice()->CreateTexture2D(&depthDesc, nullptr, &depthTexture));

    //set depth texture
    D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc = {};
    DSVDesc.Format = DXGI_FORMAT_D32_FLOAT;
    DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    DSVDesc.Texture2D.MipSlice = 0;
    DX_LOG_ERROR(context->GetDevice()->CreateDepthStencilView(depthTexture.Get(), &DSVDesc, &DSV));
}
