#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "Color.h"

namespace Engine{

	ref class Material;
	public ref class Engine::Material {
	public:

		Color^ color = gcnew Color();

		float smoothness = 0.5f;
		float reflectivity = 0.25f;

		int glow = 0;

		System::String^ textureName = "";
	};
}