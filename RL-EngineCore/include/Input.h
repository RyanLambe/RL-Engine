#pragma once

#include <Windows.h>
#include <map>

#include "types/Vec2.h"
#include "Debug.h"

#define lowPassAlpha 0.25f

enum CursorState {
	Free = 0,
	Confined = 1,
	Locked = 2,
	Hidden = 3
};

namespace Core {
	static class Input {
	public:

		//updates
		void update();
		void start(HWND window);
		~Input();

		//keys
		static bool getKey(UINT key);

		void updateKey(UINT key, bool pressed);

		//mouse
		static Vec2 getMousePos();
		static Vec2 getMouse();
		static bool getMouseButton(int button);
		static float getMouseWheel();

		void updateMouse(int button, bool pressed);
		void updateMousePos(LPARAM input);
		void updateMouseWheel(float input);

		//cursor
		static void setCursorState(CursorState state);

		//move

	private:

		//general
		static HWND window;
		static RECT windowRect;

		//keys
		static std::map<UINT, bool> keys;

		//mouse
		static bool mouseButtons[3];
		static Vec2 mousePos;
		static Vec2 deltaMousePos;
		static float mouseWheel;

		//cursor
		static CursorState state;
		static Vec2 windowCenter;

	};
}