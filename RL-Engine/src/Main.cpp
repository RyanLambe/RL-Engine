#include <Windows.h>

#include "../include/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {

	Window window(hInstance, L"Title", WS_OVERLAPPEDWINDOW, 1280, 720);

	return window.Run();
}