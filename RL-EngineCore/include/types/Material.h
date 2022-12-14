#pragma once

#include <d3d11.h>
#include "Texture.h"
#include "../Debug.h"
#include "SmartPtr.h"

namespace Core {
	class Material {
	public:
		struct MaterialInfo {
			struct {
				float r = 1;
				float g = 1;
				float b = 1;
				float a = 1;
			} color;

			float smoothness = 0.5f;
			float reflectivity = 0.25f;

			int glow = 0;

			int texId = 0;

			std::string textureName = "assets/default.png";
		} settings;

	public:

		Material();
		void Update(ID3D11Device* device, ID3D11DeviceContext* context);
		void SetTexture(std::string textureName);
		void Refresh();


		Texture texture;
	private:
		bool set = false;

		//Texture texture;

		SmartPtr<ID3D11Buffer> constBuffer;
	};
}