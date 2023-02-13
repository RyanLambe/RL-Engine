#include "../../include/types/Color.h"

using namespace Engine;

//constructors
Color::Color() {
	this->r = 1;
	this->g = 1;
	this->b = 1;
}

Color::Color(float value) {
	this->r = value;
	this->g = value;
	this->b = value;
}

Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

//other formats
Color^ Color::rgb(float r, float g, float b) {
	return gcnew Color(r, g, b);
}

Color^ Color::rgb255(float r, float g, float b) {
	return gcnew Color(r / 255.0f, g / 255.0f, b / 255.0f);
}

Color^ Color::hsl(float h, float s, float l) {
	return Color::hsl360(h * 360, s * 100, l * 100);
}

Color^ Color::hsl360(float h, float s, float l) {
	
	float a = (s/100) * System::Math::Min((l/100), 1 - (l/100));

	int r1 = (int)(0 + h / 30) % 12;
	int g1 = (int)(8 + h / 30) % 12;
	int b1 = (int)(4 + h / 30) % 12;

	float r = (l/100) - a * System::Math::Max(-1, System::Math::Min(r1 - 3, System::Math::Min(9 - r1, 1)));
	float g = (l/100) - a * System::Math::Max(-1, System::Math::Min(g1 - 3, System::Math::Min(9 - g1, 1)));
	float b = (l/100) - a * System::Math::Max(-1, System::Math::Min(b1 - 3, System::Math::Min(9 - b1, 1)));

    return gcnew Color(r, g, b);
}

Color^ Color::hex(System::String^ hexCode) {
	float r = int::Parse(hexCode->Substring(0, 2), System::Globalization::NumberStyles::HexNumber);
	float g = int::Parse(hexCode->Substring(2, 4), System::Globalization::NumberStyles::HexNumber);
	float b = int::Parse(hexCode->Substring(4, 6), System::Globalization::NumberStyles::HexNumber);
	return gcnew Color(r / 255.0f, g / 255.0f, b / 255.0f);
}