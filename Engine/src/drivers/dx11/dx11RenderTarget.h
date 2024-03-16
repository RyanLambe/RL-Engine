#pragma once

#include <cstdint>

#include "dx11.h"
#include <glm/vec4.hpp>

#include "../../graphics/RenderTarget.h"

namespace rl
{
	class DX11RenderTarget : public rl::RenderTarget
	{
	public:
		DX11RenderTarget(bool useSwapChain);

		void Enable() noexcept override;
		void Clear() noexcept override;

        void Resize(uint32_t width, uint32_t height) noexcept override;

		void SetClearColor(const glm::vec4& value) noexcept override;

        [[nodiscard]] void* GetTexture() noexcept override;

	private:
        bool useSwapChain;

		uint32_t width, height;

		glm::vec4 clearColor = glm::vec4(1, 155.0f / 255.0f, 0, 1);

        Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTexture = Microsoft::WRL::ComPtr<ID3D11Texture2D>();
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>();
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV = Microsoft::WRL::ComPtr<ID3D11DepthStencilView>();
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> resView = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>();
	};
}
