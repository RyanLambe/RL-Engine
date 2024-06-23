#pragma once

#include <memory>
#include <vector>
#include "../types/Vertex.h"
#include "Context.h"

namespace rl {
	class VertexBuffer {
	public:
		virtual ~VertexBuffer();

		static std::shared_ptr<VertexBuffer> Create(const std::vector<Vertex>& data, bool dynamic, const std::weak_ptr<Context>& context);

		virtual void Enable() = 0;

		virtual void Set(const std::vector<Vertex>& data) = 0;

	};
}