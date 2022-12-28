#pragma once

#include "Graphics.h"
#include "objects/Entity.h"

class Window
{
public:
	Window(HINSTANCE hInstance, LPCWSTR name, DWORD style, int width, int height);
	~Window();

	int Run();

private:
	bool WindowClosed(int* quitMessage);
	static LRESULT CALLBACK WindowProcThunk(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND hwnd;
	Graphics gfx;
};