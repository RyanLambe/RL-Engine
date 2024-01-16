#pragma once
#include <memory>
#include <glm/vec4.hpp>

namespace rl
{
	class RenderTarget
	{
	public:
		static std::shared_ptr<RenderTarget> Create();
		static std::shared_ptr<RenderTarget> Create(uint32_t width, uint32_t height);

		virtual void Enable() const noexcept = 0;
		virtual void Clear() noexcept = 0;

		virtual void SetClearColor(const glm::vec4& value) noexcept = 0;
		virtual void EnableDepthTest(bool enable = true) noexcept = 0;

	};
}
