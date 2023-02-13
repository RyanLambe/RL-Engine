#pragma once
#include <cmath>

namespace Engine {
	public ref class Color {
	public:
		//conponents
		float r;
		float g;
		float b;

		//constructors
		Color();
		Color(float value);
		Color(float r, float g, float b);

		static Color^ rgb(float r, float g, float b);
		static Color^ rgb255(float r, float g, float b);
		static Color^ hsl(float h, float s, float l);
		static Color^ hsl360(float h, float s, float l);
		static Color^ hex(System::String^ hexCode);

	};
}