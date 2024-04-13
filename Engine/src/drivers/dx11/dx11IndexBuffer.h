#pragma once

#include <vector>

#include "dx11.h"
#include "dx11Context.h"

#include "../../graphics/IndexBuffer.h"

namespace rl {
	class DX11IndexBuffer : public rl::IndexBuffer {
	public:
		DX11IndexBuffer() = delete;
		DX11IndexBuffer(const std::vector<uint32_t>& data, bool dynamic, const std::weak_ptr<DX11Context>& contextPtr);

		void Enable() override;

		void Set(const std::vector<uint32_t>& data) override;

	private:
		std::weak_ptr<DX11Context> contextPtr;
        bool isDynamic;

		Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>();
	};
}