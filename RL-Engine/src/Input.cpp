#include "../include/Input.h"

//setup static variables
HWND Input::window;

std::map<UINT, bool> Input::keys;

bool Input::mouseButtons[3]; 
Vec2 Input::mousePos;
float Input::mouseWheel;

//updates to be used by windows class
void Input::start(HWND window)
{
	//save the windows HWND
	Input::window = window;

	//get raw input
	RAWINPUTDEVICE rawInputDevice;
	rawInputDevice.usUsagePage = 0x01;
	rawInputDevice.usUsage = 0x02;
	rawInputDevice.dwFlags = 0;
	rawInputDevice.hwndTarget = NULL;

	// register the raw input device
	if (!RegisterRawInputDevices(&rawInputDevice, 1, sizeof(RAWINPUTDEVICE)))
	{
		throw std::exception("Mouse not connected");
	}
}

void Input::update()
{
	mousePos = Vec2(0, 0);
	mouseWheel = 0;
}

void Input::updateKey(UINT key, bool pressed)
{
	if (!keys.contains(key)) {
		keys.emplace(key, pressed);
		return;
	}

	keys.at(key) = pressed;
}

void Input::updateMouse(int button, bool pressed)
{
	mouseButtons[button] = pressed;
}

void Input::updateMousePos(HRAWINPUT input)
{
	//get raw mouse input
	UINT dataSize;
	GetRawInputData(input, RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

	BYTE* rawInputData = new BYTE[dataSize];
	GetRawInputData(input, RID_INPUT, rawInputData, &dataSize, sizeof(RAWINPUTHEADER));

	// save mouse pos
	RAWINPUT* rawInput = (RAWINPUT*)rawInputData;
	if (rawInput->header.dwType == RIM_TYPEMOUSE)
	{
		mousePos = Vec2(rawInput->data.mouse.lLastX, rawInput->data.mouse.lLastY);
	}

	// clean up
	delete[] rawInputData;
}

void Input::updateMouseWheel(float input)
{
	mouseWheel = input;
}

//static functions to used by user
bool Input::getKey(UINT key)
{
	if (keys.contains(key))
		return keys.at(key);
	return false;
}

Vec2 Input::getMousePos()
{
	POINT pnt;
	GetCursorPos(&pnt);
	ScreenToClient(window, &pnt);
	return Vec2(pnt.x, pnt.y);
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
