#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../RL-EngineCore/include/Window.h"
#endif

namespace Engine {

	public ref class Time {
	public:

		//timer subclass here

		static float getTime();
		static float deltaTime();

	};

}