#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

namespace Engine {
	public ref class Vec2 {
	public:
		//components
		float x;
		float y;

		//constructors
		Vec2();
		Vec2(float value);
		Vec2(float x, float y);
		Vec2(Core::Vec2 vec2);

		//functions
		//test a
		static float distance(Vec2^ a, Vec2^ b);
		Core::Vec2 getCoreFormat();

		//operators
		static Vec2^ operator+(Vec2^ left, Vec2^ right);
		static Vec2^ operator+(Vec2^ left, float right);
		static Vec2^ operator+(float left, Vec2^ right);
		static void operator+=(Vec2^ left, Vec2^ right);
		static void operator+=(Vec2^ left, float right);

		static Vec2^ operator-(Vec2^ left, Vec2^ right);
		static Vec2^ operator-(Vec2^ left, float right);
		static Vec2^ operator-(float left, Vec2^ right);
		static Vec2^ operator-(Vec2^ vec);
		static void operator-=(Vec2^ left, Vec2^ right);
		static void operator-=(Vec2^ left, float right);

		static Vec2^ operator*(Vec2^ left, Vec2^ right);
		static Vec2^ operator*(Vec2^ left, float right);
		static Vec2^ operator*(float left, Vec2^ right);
		static void operator*=(Vec2^ left, Vec2^ right);
		static void operator*=(Vec2^ left, float right);

		static Vec2^ operator/(Vec2^ left, Vec2^ right);
		static Vec2^ operator/(Vec2^ left, float right);
		static Vec2^ operator/(float left, Vec2^ right);
		static void operator/=(Vec2^ left, Vec2^ right);
		static void operator/=(Vec2^ left, float right);
	};
}