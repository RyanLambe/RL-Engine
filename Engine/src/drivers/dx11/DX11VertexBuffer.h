#pragma once

#include <vector>

#include "dx11.h"

#include "../../graphics/VertexBuffer.h"
#include "../../types/Vertex.h"
#include "dx11Context.h"

namespace rl {
	class DX11VertexBuffer : public rl::VertexBuffer
	{
	public:
		DX11VertexBuffer() = delete;
		DX11VertexBuffer(const std::vector<Vertex>& data, bool dynamic, const std::weak_ptr<DX11Context>& contextPtr);

		void Enable() override;

		void Set(const std::vector<Vertex>& data) override;

	private:
        std::weak_ptr<DX11Context> contextPtr;
		bool isDynamic;

		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>();
	};
}