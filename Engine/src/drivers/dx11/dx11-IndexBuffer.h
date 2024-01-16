#pragma once

#include <vector>

#include <d3d11.h>
#include <wrl.h>

#include "../../graphics/IndexBuffer.h"

namespace rl::impl {
	class DX11IndexBuffer : public rl::IndexBuffer {
	public:
		DX11IndexBuffer() = delete;
		DX11IndexBuffer(const std::vector<uint32_t>& data, bool dynamic);

		void Enable() override;

		void Set(const std::vector<uint32_t>& data) override;

	private:
		bool isDynamic;

		Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>();
	};
}