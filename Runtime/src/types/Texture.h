#pragma once

#include <d3d11.h>
#include <string>
#include <vector>
#include <map>
#include <wrl.h>

//external
//https://lodev.org/lodepng/
#include "../../external/LodePng/lodepng.h"

#include "../Debug.h"

namespace Core {
	class Texture {
	public:
		Texture();
		Texture(const Texture&) = delete;
		void Set(std::string fileName);
		void Update(ID3D11Device* device, ID3D11DeviceContext* context);
		int getId();
		float* getAverage();

	private:

		float avColour[3] = { 0, 0, 0 };

		std::string name;

		static int nextId;
		static std::map<std::string, int> idMap;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D = Microsoft::WRL::ComPtr<ID3D11Texture2D>();
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texView = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>();

	};
}
