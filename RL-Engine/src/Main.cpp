#include "../include/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {

	//creates and runs engine window, catchs all exceptions
	try {
		//setup
		Debug::start(true);
		Window window(hInstance, L"RL-Engine", WS_OVERLAPPEDWINDOW, 1280, 720);
		
		//run
		int out = window.Run();

		//close
		Debug::close();
		return out;
	}
	catch (std::exception& e) {
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONEXCLAMATION);
	}
	catch ( ... ) {
		MessageBoxA(nullptr, "Check log file for more info.", "Error", MB_OK | MB_ICONEXCLAMATION);
	}

	//didnt return in try therefore error
	Debug::close();
	return -1;
}