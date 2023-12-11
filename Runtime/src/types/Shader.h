#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

#include "../Debug.h"

namespace Core {
	class Shader {
	public:
		Shader();
		Shader(const Shader&) = delete;
		void Start(ID3D11Device* device, ID3D11DeviceContext* context);

	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = Microsoft::WRL::ComPtr<ID3D11VertexShader>();
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = Microsoft::WRL::ComPtr<ID3D11PixelShader>();
		Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = Microsoft::WRL::ComPtr<ID3D11InputLayout>();
		Microsoft::WRL::ComPtr<ID3DBlob> blob = Microsoft::WRL::ComPtr<ID3DBlob>();
	};
}
