#pragma once

#include <cstdint>

#include "dx11.h"
#include <glm/vec4.hpp>
#include <optional>

#include "../../graphics/RenderTarget.h"
#include "dx11Context.h"

namespace rl
{
	class DX11RenderTarget : public rl::RenderTarget
	{
	public:
		DX11RenderTarget(const std::weak_ptr<Window>& windowPtr, const std::weak_ptr<DX11Context>& contextPtr);
        DX11RenderTarget(uint32_t width, uint32_t height, const std::weak_ptr<DX11Context>& contextPtr);

		void Enable() override;
		void Clear() override;

        void Resize(uint32_t width, uint32_t height) override;

		void SetClearColor(const glm::vec4& value) noexcept override;

        [[nodiscard]] void* GetTexture() noexcept override;

	private:

        void Refresh();

        std::weak_ptr<DX11Context> contextPtr;
        std::optional<std::weak_ptr<Window>> windowPtr = std::nullopt;

		uint32_t width, height;
		glm::vec4 clearColor = glm::vec4(1, 155.0f / 255.0f, 0, 1);

        Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTexture = Microsoft::WRL::ComPtr<ID3D11Texture2D>();
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>();
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV = Microsoft::WRL::ComPtr<ID3D11DepthStencilView>();
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> resView = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>();
	};
}
