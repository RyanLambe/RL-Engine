#pragma once
#include <memory>
#include <glm/vec4.hpp>

namespace rl
{
	class RenderTarget
	{
	public:
		static std::shared_ptr<RenderTarget> Create(bool useSwapChain);

		virtual void Enable() noexcept = 0;
		virtual void Clear() noexcept = 0;

        virtual void Resize(uint32_t width, uint32_t height) noexcept = 0;

		virtual void SetClearColor(const glm::vec4& value) noexcept = 0;

        [[nodiscard]] virtual void* GetTexture() noexcept = 0;

	};
}
