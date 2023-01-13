#include "../include/Window.h"

Core::Window* Core::Window::main = nullptr;

Core::Window::Window(HINSTANCE hInstance, std::wstring name, DWORD style, int width, int height) {
	main = this;
	// Create class for window
	WNDCLASS wClass = {};

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WindowProcThunk;
	wClass.lpszClassName = name.c_str();
	
	RegisterClass(&wClass);

	// get size of window
	RECT size;
	
	size.left = 100;
	size.right = width + size.left;
	size.top = 100;
	size.bottom = height + size.top;

	//set size and check for error
	if (AdjustWindowRect(&size, style, false) == 0) {
		throw std::exception(Debug::TranslateHResult(GetLastError()).c_str());
	}

	// Create window
	hwnd = CreateWindow(name.c_str(), name.c_str(), style, CW_USEDEFAULT, CW_USEDEFAULT, size.right - size.left, size.bottom - size.top, NULL, NULL, hInstance, this);

	//check for error
	if (hwnd == NULL) {
		throw std::exception(Debug::TranslateHResult(GetLastError()).c_str());
	}
	
	//setup input, debug, and graphics
	input.start(hwnd);
	debug.start(true);

	Debug::log("test25");

	ShowWindow(hwnd, SW_SHOW);
	gfx.Start(hwnd, size.right - size.left, size.bottom - size.top);

	std::string skybox[6];
	skybox[0] = "assets/skybox/top.png";
	skybox[1] = "assets/skybox/bottom.png";
	skybox[2] = "assets/skybox/left.png";
	skybox[3] = "assets/skybox/right.png";
	skybox[4] = "assets/skybox/front.png";
	skybox[5] = "assets/skybox/back.png";
	gfx.setSkybox(skybox);
}

Core::Window::ExitCode Core::Window::Spagetti()
{
	ExitCode out;
	try {
		if (!WindowClosed(&out.exitCode)) {

			time.update();
			input.update();
			gfx.Draw();
			gfx.EndFrame();
			out.close = false;
		}
		else {
			out.close = true;
		}
		return out;
	}
	catch (std::exception& e) {
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) {
		MessageBoxA(nullptr, "Check log file for more info.", "Error", MB_OK | MB_ICONEXCLAMATION);
	}

	out.close = true;
	//out.exitCode = -1;
	return out;
}

Core::Window::~Window()
{
	if(hwnd != nullptr)
		DestroyWindow(hwnd);
}

float angle = 0.0f;

Core::Graphics* Core::Window::getGraphics()
{
	return &gfx;
}

bool Core::Window::WindowClosed(int* quitMessage)
{
	// for all messages in queue
	MSG msg = {};
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		// if message is quit, set quitMessage and return true
		if (msg.message == WM_QUIT) {
			*quitMessage = (int)msg.wParam;
			return true;
		}

		//deal with messages
		TranslateMessage(&msg);
		Debug::logErrorCode(DispatchMessage(&msg));
	}

	// if not quitting, return false
	return false;
}

LRESULT Core::Window::WindowProcThunk(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// save pointer to window in hwnd from create method
	if (uMsg == WM_CREATE) {
		//get pointer to window from constructor
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* wnd = static_cast<Window*>(pCreate->lpCreateParams);
		
		//save window pointer in hwnd
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));

		return wnd->WindowProc(uMsg, wParam, lParam);
	}

	// if pointer to window hasnt been set
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	if(ptr == 0)
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

	// run proper window proc
	Window* wnd = reinterpret_cast<Window*>(ptr);
	return wnd->WindowProc(uMsg, wParam, lParam);
}

LRESULT Core::Window::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{

	//keyboard
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
		input.updateKey(wParam, true);
		break;

	case WM_SYSKEYUP:
	case WM_KEYUP:
		input.updateKey(wParam, false);
		break;

	//mouse buttons
	case WM_LBUTTONDOWN:
		input.updateMouse(0, true);
		break;
	case WM_LBUTTONUP:
		input.updateMouse(0, false);
		break;

	case WM_RBUTTONDOWN:
		input.updateMouse(1, true);
		break;
	case WM_RBUTTONUP:
		input.updateMouse(1, false);
		break;

	case WM_MBUTTONDOWN:
		input.updateMouse(2, true);
		break;
	case WM_MBUTTONUP:
		input.updateMouse(2, false);
		break;

	//mouse pos
	case WM_MOUSEWHEEL:
		if(GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			input.updateMouseWheel(-1);
		else
			input.updateMouseWheel(1);
		break;

	case WM_INPUT:
		input.updateMousePos(lParam);
		break;
	
	//close window
	case WM_DESTROY:
		PostQuitMessage(25);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
