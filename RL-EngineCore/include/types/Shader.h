#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <filesystem>

#include "../Debug.h"
#include "SmartPtr.h"

namespace Core {
	class Shader {
	public:
		void Start(ID3D11Device* device, ID3D11DeviceContext* context);

	private:
		SmartPtr<ID3D11VertexShader> vertexShader = SmartPtr<ID3D11VertexShader>();
		SmartPtr<ID3D11PixelShader> pixelShader = SmartPtr<ID3D11PixelShader>();
		SmartPtr<ID3D11InputLayout> inputLayout = SmartPtr<ID3D11InputLayout>();
		SmartPtr<ID3DBlob> blob = SmartPtr<ID3DBlob>();
	};
}
