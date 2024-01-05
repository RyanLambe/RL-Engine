#pragma once

#include <cstdint>

#include <d3d11.h>
#include <wrl.h>
#include <glm/vec4.hpp>

#include "src/graphics/RenderTarget.h"

namespace rl::impl
{
	class DX11RenderTarget : public rl::RenderTarget
	{
	public:
		DX11RenderTarget(); // based on window size
		DX11RenderTarget(uint32_t width, uint32_t height); // custom size

		void Enable() const noexcept override;
		void Clear() noexcept override;

		void SetClearColor(const glm::vec4& value) noexcept override;
		void EnableDepthTest(bool enable = true) noexcept override;

	private:

		void Resize(uint32_t width, uint32_t height) noexcept;

		bool windowSize;
		bool depthEnabled;

		uint32_t width, height;

		glm::vec4 clearColor = glm::vec4(1, 155.0f / 255.0f, 0, 1);


		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture = Microsoft::WRL::ComPtr<ID3D11Texture2D>();
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>();
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV = Microsoft::WRL::ComPtr<ID3D11DepthStencilView>();
	};
}
