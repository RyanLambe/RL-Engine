#pragma once
#include "../../pch.h"

namespace Engine{
	public ref class Material {
	public:

		ref struct Colour {
			float r = 1;
			float g = 1;
			float b = 1;
			float a = 1;
		} color;

		float smoothness = 0.5f;
		float reflectivity = 0.25f;

		int glow = 0;

		System::String^ textureName;
	};
}