#pragma once

#include <vector>
#include <memory>
#include "GraphicsContext.h"

namespace rl {
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		static std::shared_ptr<IndexBuffer> Create(const std::vector<uint32_t>& data, bool dynamic, const std::weak_ptr<GraphicsContext>& context);

		virtual void Enable() = 0;

		virtual void Set(const std::vector<uint32_t>& data) = 0;

	};
}