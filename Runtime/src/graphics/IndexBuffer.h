#pragma once

#include <vector>
#include <memory>

namespace rl {
	class IndexBuffer {
	public:

		static std::shared_ptr<IndexBuffer> Create(const std::vector<uint32_t>& data, bool dynamic = false);

		virtual void Enable() = 0;

		virtual void Set(const std::vector<uint32_t>& data) = 0;

	};
}