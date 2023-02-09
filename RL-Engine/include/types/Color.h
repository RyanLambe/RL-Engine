#pragma once

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
	};
}