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
	cam.getTransform()->setPosition(0, 10, -10);
	cam.getTransform()->setRotation(45, 0, 0);
	comp.fov = 60;

	/*Entity Dirlight;
	DirectionalLight comp2(&Dirlight);
	gfx.setDirectionalLight(&comp2);
	Dirlight.getTransform()->setRotation(-45, 45, 0);
	comp2.Colour = Vec3(1, 1, 1);*/

	Entity Pntlight;
	PointLight* pnt = gfx.createPointLight(&Pntlight);
	pnt->Colour = Vec3(1, 0, 0);
	Pntlight.getTransform()->setScale(0.1f, 0.1f, 0.1f);
	MeshRenderer* light = gfx.createMesh(&Pntlight);
	light->getMesh()->ImportObj("assets/ssphere.obj");
	light->getMaterial()->settings.color = {1, 0, 0, 1};
	light->getMaterial()->settings.glow = 1;
	
	Entity Pntlight2;
	PointLight* pnt2 = gfx.createPointLight(&Pntlight2);
	pnt2->Colour = Vec3(0, 1, 0);
	Pntlight2.getTransform()->setScale(0.1f, 0.1f, 0.1f);
	MeshRenderer* light2 = gfx.createMesh(&Pntlight2);
	light2->getMesh()->ImportObj("assets/ssphere.obj");
	light2->getMaterial()->settings.color = { 0, 1, 0, 1 };
	light2->getMaterial()->settings.glow = 1;

	Entity cube1;
	gfx.createMesh(&cube1);
	cube1.getTransform()->setPosition(0, 0, 0);
	cube1.getComponent<MeshRenderer>()->getMaterial()->settings.color = {1, 1, 1};// { 0, 1, 0.435f, 1 };

	Entity cube2;
	gfx.createMesh(&cube2);
	cube2.setParent(&cube1);
	cube2.getTransform()->setPosition(-3, 0, 0);
	cube2.getTransform()->setScale(0.5);
	cube2.getComponent<MeshRenderer>()->getMaterial()->settings.color = { 0, 0.6706f, 1, 1 };

	/*Entity floor;
	MeshRenderer* floorRend = gfx.createMesh(&floor);
	floorRend->getMesh()->ImportObj("assets/plane.obj");
	floorRend->getMaterial()->settings.glow = 1;*/
	//floor.getTransform()->setScale(10, 10, 10);

	std::string skybox[6];
	skybox[0] = "assets/skybox/top.png";
	skybox[1] = "assets/skybox/bottom.png";
	skybox[2] = "assets/skybox/left.png";
	skybox[3] = "assets/skybox/right.png";
	skybox[4] = "assets/skybox/front.png";
	skybox[5] = "assets/skybox/back.png";
	gfx.setSkybox(skybox);

	while (!WindowClosed(&exitCode))
	{
		//code
		angle += 0.05f;
		//Dirlight.getTransform()->setRotation(5 * angle, 10 * angle, 0);

		//cam.getTransform()->setRotation(angle, angle, 0);

		Pntlight.getTransform()->setPosition(angle/20 - 5, 3, 0);
		Pntlight2.getTransform()->setPosition(-angle / 20 + 5, 3, angle / 20 - 5);

		//cube1.getTransform()->setRotation(angle, 0, angle);
		//cube2.getTransform()->setRotation(0, 0, angle);

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
