#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

namespace Engine {
	public ref class Vec3 {
	public:

		//conponents
		float x;
		float y;
		float z;

		//constructors
		Vec3();
		Vec3(float value);
		Vec3(float x, float y, float z);
		Vec3(Core::Vec3 vec3);

		//functions
		static float distance(Vec3^ a, Vec3^ b);
		Core::Vec3 getCoreFormat();

		//operators
		Vec3^ operator+(Vec3^ other);
		Vec3^ operator+(float other);
		void operator+=(Vec3^ other);
		void operator+=(float other);

		Vec3^ operator-(Vec3^ other);
		Vec3^ operator-(float other);
		void operator-=(Vec3^ other);
		void operator-=(float other);

		Vec3^ operator*(Vec3^ other);
		Vec3^ operator*(float other);
		void operator*=(Vec3^ other);
		void operator*=(float other);

		Vec3^ operator/(Vec3^ other);
		Vec3^ operator/(float other);
		void operator/=(Vec3^ other);
		void operator/=(float other);

	};
}