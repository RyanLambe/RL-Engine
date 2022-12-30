#pragma once

#include <Windows.h>
#include <map>

#include "types/Vec2.h"

static class Input {
public:

	//updates
	void update();
	void updateKey(UINT key, bool pressed);
	void updateMouse(int button, bool pressed);
	void updateMousePos(HRAWINPUT input);
	void updateMouseWheel(float input);
	void start(HWND window);

	//keys
	static bool getKey(UINT key);

	//mouse
	static Vec2 getMousePos();
	static Vec2 getMouse();
	static bool getMouseButton(int button);
	static float getMouseWheel();

private:

	//general
	static HWND window;

	//keys
	static std::map<UINT, bool> keys;

	//mouse
	static bool mouseButtons[3];
	static Vec2 mousePos;
	static float mouseWheel;

};