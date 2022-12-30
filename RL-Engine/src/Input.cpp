#include "../include/Input.h"

#include "../include/Graphics.h"

//setup static variables
HWND Input::window;
RECT Input::windowRect;

std::map<UINT, bool> Input::keys;

bool Input::mouseButtons[3]; 
Vec2 Input::mousePos;
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
	rawInputDevice.hwndTarget = NULL;

	// register the raw input device
	if (!RegisterRawInputDevices(&rawInputDevice, 1, sizeof(RAWINPUTDEVICE)))
	{
		throw std::exception("Mouse not connected");
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
	//reset values
	mousePos = Vec2(0, 0);
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
	ScreenToClient(window, &pnt);
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
