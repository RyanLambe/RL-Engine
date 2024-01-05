#pragma once

#include <d3d11.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include "../../graphics/Context.h"

namespace rl::impl {
	class DX11Context : public Context
	{
	public:

		DX11Context(const Context&) = delete;
		DX11Context() = delete;
		DX11Context(HWND hwnd, uint32_t width, uint32_t height);

		void DrawIndexed(uint32_t size) const noexcept override;

		void Present() const noexcept override;

		void EnableTransparency(bool enable = true) const noexcept;
		void EnableDepth(bool enable = true) const noexcept;

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
	};
}