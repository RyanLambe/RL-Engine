#include "../include/Window.h"

Window::Window(HINSTANCE hInstance, LPCWSTR name, DWORD style, int width, int height)
{
	// Create class for window
	WNDCLASS wClass = {};

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WindowProcThunk;
	wClass.lpszClassName = name;
	
	RegisterClass(&wClass);

	// get size of window
	RECT size;
	
	size.left = 100;
	size.right = width + size.left;
	size.top = 100;
	size.bottom = height + size.top;

	if (AdjustWindowRect(&size, style, false) == 0) {
		throw WndExcept(GetLastError());
	}

	// Create window
	hwnd = CreateWindow(name, name, style, CW_USEDEFAULT, CW_USEDEFAULT, size.right - size.left, size.bottom - size.top, NULL, NULL, hInstance, this);

	if (hwnd == NULL) {
		throw WndExcept(GetLastError());
	}

	ShowWindow(hwnd, SW_SHOW);
	
	//create graphics
	gfx.Start(hwnd);
}

Window::~Window()
{
	DestroyWindow(hwnd);
}

float angle = 0.0f;

int Window::Run()
{
	int exitCode;

	Entity cam;
	Camera comp(&cam);
	cam.addComponent(&comp);
	cam.getTransform()->setPosition(0, 0, 5);
	comp.fov = 60;

	Entity Dirlight;
	DirectionalLight comp2(&Dirlight);
	gfx.setDirectionalLight(&comp2);
	Dirlight.getTransform()->setRotation(-45, 0, 45);

	Entity cube1;
	gfx.createMesh(&cube1);
	cube1.getTransform()->setPosition(0, 0, 0);
	cube1.getComponent<MeshRenderer>()->getMaterial()->settings.color = { 0, 1, 0, 1 };

	Entity cube2;
	gfx.createMesh(&cube2);
	cube2.setParent(&cube1);
	cube2.getTransform()->setPosition(-3, 0, 0);
	cube2.getTransform()->setScale(0.5);
	cube2.getComponent<MeshRenderer>()->getMaterial()->settings.color = { 0, 0, 1, 1 };

	while (!WindowClosed(&exitCode))
	{
		//code
		angle += 0.01f;
		Dirlight.getTransform()->setRotation(0, angle, 45);

		cube1.getTransform()->setRotation(angle, 0, angle);
		cube2.getTransform()->setRotation(0, 0, angle);

		gfx.Draw();
		gfx.EndFrame();
	}
	return exitCode;
}

bool Window::WindowClosed(int* quitMessage)
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
		DispatchMessage(&msg);
	}

	// if not quitting, return false
	return false;
}

LRESULT Window::WindowProcThunk(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT Window::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
