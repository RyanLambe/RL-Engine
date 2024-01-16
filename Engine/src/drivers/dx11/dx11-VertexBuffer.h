#pragma once

#include <vector>

#include <d3d11.h>
#include <wrl.h>

#include "../../graphics/VertexBuffer.h"
#include "../../types/Vertex.h"

namespace rl::impl {
	class DX11VertexBuffer : public rl::VertexBuffer
	{
	public:
		DX11VertexBuffer() = delete;
		DX11VertexBuffer(const std::vector<Vertex>& data, bool dynamic);

		void Enable() override;

		void Set(const std::vector<Vertex>& data) override;

	private:
		bool isDynamic;

		Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>();
	};
}