#pragma once

#include "dx11.h"

#include "../../graphics/Context.h"

namespace rl {
	class DX11Context : public Context
	{
	public:

		DX11Context(const Context&) = delete;
		DX11Context() = delete;
		DX11Context(HWND hwnd, uint32_t width, uint32_t height);

		void DrawIndexed(uint32_t size) const noexcept override;

		void Present() const override;

		void EnableTransparency(bool enable = true) const noexcept;
		void EnableDepth(bool enable = true) const;

		static ID3D11DeviceContext* GetContext();
		static ID3D11Device* GetDevice();
		static IDXGISwapChain* GetSwap();

		static uint32_t GetWindowWidth();
		static uint32_t GetWindowHeight();

	private:

		static DX11Context* mainContext;

		uint32_t width, height;
		uint32_t vsync = 0;

		Microsoft::WRL::ComPtr<IDXGISwapChain> swap = Microsoft::WRL::ComPtr<IDXGISwapChain>();
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context = Microsoft::WRL::ComPtr<ID3D11DeviceContext>();
		Microsoft::WRL::ComPtr<ID3D11Device> device = Microsoft::WRL::ComPtr<ID3D11Device>();

		// textures
		Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler = Microsoft::WRL::ComPtr<ID3D11SamplerState>();

        //todo: move to separate shader class
        void StartShader(ID3D11Device* device, ID3D11DeviceContext* context);
        Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = Microsoft::WRL::ComPtr<ID3D11VertexShader>();
        Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = Microsoft::WRL::ComPtr<ID3D11PixelShader>();
        Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = Microsoft::WRL::ComPtr<ID3D11InputLayout>();
        Microsoft::WRL::ComPtr<ID3DBlob> blob = Microsoft::WRL::ComPtr<ID3DBlob>();
	};
}