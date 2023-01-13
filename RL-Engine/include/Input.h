#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../RL-EngineCore/include/Window.h"
#endif

#include "types/Vec2.h"

namespace Engine {

	enum CursorState {
		Free = 0,
		Confined = 1,
		Locked = 2,
		Hidden = 3
	};

	public ref class Input {
	public:
		//keyboard
		static bool getKey(UINT key);

		//mouse
		static Vec2^ getMousePos();
		static Vec2^ getMouse();
		static bool getMouseButton(int button);
		static float getMouseWheel();

		//cursor
		static void setCursorState(int state);
	};


}