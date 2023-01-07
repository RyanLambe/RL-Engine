#include "../include/Input.h"

#include "../include/Graphics.h"

using namespace Core;

//setup static variables
HWND Input::window;
RECT Input::windowRect;

std::map<UINT, bool> Input::keys;

bool Input::mouseButtons[3]; 
Vec2 Input::mousePos = Vec2(0, 0);
Vec2 Input::deltaMousePos = Vec2(0, 0);
float Input::mouseWheel;

CursorState Input::state = CursorState::Free;
Vec2 Input::windowCenter;


//updates

void Input::start(HWND window)
{
	//save input values
	Input::window = window;

	//get raw input
	RAWINPUTDEVICE rawInputDevice;
	rawInputDevice.usUsagePage = 0x01;
	rawInputDevice.usUsage = 0x02;
	rawInputDevice.dwFlags = 0;
	rawInputDevice.hwndTarget = window;

	// register the raw input device
	if (!RegisterRawInputDevices(&rawInputDevice, 1, sizeof(RAWINPUTDEVICE)))
	{
		throw std::exception("Input not connected");
	}
}

Input::~Input()
{
	//free cursor
	ClipCursor(nullptr);
	ShowCursor(true);
}

void Input::update()
{
	//update values
	mousePos -= Vec2(mousePos.x * lowPassAlpha, mousePos.y * lowPassAlpha);
	mouseWheel = 0;
	GetWindowRect(window, &windowRect);

	//if window isnt active, free cursor
	if (GetActiveWindow() != window) {
		ClipCursor(nullptr);
		ShowCursor(true);
		return;
	}

	//get screen center
	RECT clientRect;
	GetClientRect(window, &clientRect);
	MapWindowPoints(window, NULL, (POINT*)&clientRect, 2);

	windowCenter = Vec2((clientRect.left + clientRect.right) / 2, (clientRect.top + clientRect.bottom) / 2);

	//lock cursor if set to
	if (state == CursorState::Confined) 
		ClipCursor(&windowRect);
	
	if (state == CursorState::Locked || state == CursorState::Hidden)
		SetCursorPos(windowCenter.x, windowCenter.y);
	
}


//keyboard

void Input::updateKey(UINT key, bool pressed)
{
	//add key if doesnt exist
	if (!keys.contains(key)) {
		keys.emplace(key, pressed);
		return;
	}

	keys.at(key) = pressed;
}

bool Input::getKey(UINT key)
{
	if (keys.contains(key))
		return keys.at(key);
	return false;
}


//mouse

Vec2 Input::getMousePos()
{
	POINT pnt;
	GetCursorPos(&pnt);
	return Vec2(pnt.x, pnt.y);
}

void Input::updateMouse(int button, bool pressed)
{
	mouseButtons[button] = pressed;
}

Vec2 Input::getMouse()
{
	return mousePos;
}

bool Input::getMouseButton(int button)
{
	return mouseButtons[button];
}

float Input::getMouseWheel()
{
	return mouseWheel;
}

void Input::updateMousePos(LPARAM lparam)
{
	//get raw mouse input
	HRAWINPUT hInput = (HRAWINPUT)lparam;
	RAWINPUT input = { 0 };

	UINT size = sizeof(RAWINPUT);
	GetRawInputData(hInput, RID_INPUT, &input, &size, sizeof(RAWINPUTHEADER));
	if (RIM_TYPEMOUSE == input.header.dwType)
	{
		//update mouse pos value
		mousePos.x = input.data.mouse.lLastX;
		mousePos.y = input.data.mouse.lLastY;
	}
}

void Input::updateMouseWheel(float input)
{
	mouseWheel = input;
}


//cursor

void Input::setCursorState(CursorState state)
{
	//save state
	Input::state = state;

	//show/hide cursor
	if (state == CursorState::Hidden) 
		ShowCursor(false);
	else
		ShowCursor(true);
}
