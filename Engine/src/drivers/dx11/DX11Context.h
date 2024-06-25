#pragma once

#include "DX11.h"

#include "../../graphics/GraphicsContext.h"

namespace rl {
	class DX11Context : public GraphicsContext
	{
	public:

		DX11Context(const GraphicsContext&) = delete;
		DX11Context() = delete;
		explicit DX11Context(Window* window);

		void DrawIndexed(uint32_t size) const noexcept override;

		void Present() const override;

        [[nodiscard]] void* GetDXDevice() const override;
        [[nodiscard]] void* GetDXContext() const override;

		void EnableTransparency(bool enable = true) const noexcept;
		void EnableDepth(bool enable = true) const;

		ID3D11DeviceContext* GetContext();
		ID3D11Device* GetDevice();
		IDXGISwapChain* GetSwap();

	private:
		uint32_t vsync = 0;

		Microsoft::WRL::ComPtr<IDXGISwapChain> swap = Microsoft::WRL::ComPtr<IDXGISwapChain>();
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context = Microsoft::WRL::ComPtr<ID3D11DeviceContext>();
		Microsoft::WRL::ComPtr<ID3D11Device> device = Microsoft::WRL::ComPtr<ID3D11Device>();

		// textures
		Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler = Microsoft::WRL::ComPtr<ID3D11SamplerState>();
	};
}