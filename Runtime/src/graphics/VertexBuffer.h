#pragma once

#include <memory>
#include <vector>
#include "../types/Vertex.h"

namespace rl {
	class VertexBuffer {
	public:

		static std::shared_ptr<VertexBuffer> Create(const std::vector<Vertex>& data, bool dynamic = false);

		virtual void Enable() = 0;

		virtual void Set(const std::vector<Vertex>& data) = 0;

	};
}