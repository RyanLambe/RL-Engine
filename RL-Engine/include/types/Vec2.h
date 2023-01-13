#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "Managed.h"

namespace Engine {
	public ref class Vec2 : Managed<Core::Vec2> {
	public:
		//components
		float x;
		float y;

		//constructors
		Vec2();
		Vec2(float value);
		Vec2(float x, float y);
		Vec2(Core::Vec2* vec2);

		//functions
		static float distance(Vec2^ a, Vec2^ b);

		//operators
		Vec2^ operator+(Vec2^ other);
		Vec2^ operator+(float other);
		void operator+=(Vec2^ other);
		void operator+=(float other);

		Vec2^ operator-(Vec2^ other);
		Vec2^ operator-(float other);
		void operator-=(Vec2^ other);
		void operator-=(float other);

		Vec2^ operator*(Vec2^ other);
		Vec2^ operator*(float other);
		void operator*=(Vec2^ other);
		void operator*=(float other);

		Vec2^ operator/(Vec2^ other);
		Vec2^ operator/(float other);
		void operator/=(Vec2^ other);
		void operator/=(float other);

	};
}