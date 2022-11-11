#include "../include/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {

	//creates and runs engine window, catchs all exceptions
	try {
		Window window(hInstance, L"RL-Engine", WS_OVERLAPPEDWINDOW, 1280, 720);
		return window.Run();
	}
	catch (EngineException& e) {
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (std::exception& e) {
		MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch ( ... ) {
		MessageBoxA(nullptr, "Unknown Details", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	//didnt return in try therefore error
	return -1;
}