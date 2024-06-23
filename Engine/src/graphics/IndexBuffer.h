#pragma once

#include <vector>
#include <memory>
#include "Context.h"

namespace rl {
	class IndexBuffer {
	public:

		static std::shared_ptr<IndexBuffer> Create(const std::vector<uint32_t>& data, bool dynamic, const std::weak_ptr<Context>& context);

		virtual void Enable() = 0;

		virtual void Set(const std::vector<uint32_t>& data) = 0;

	};
}