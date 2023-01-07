#include "../include/Window.h"

#include <random>

using namespace Core;

Window* Window::main = nullptr;

Window::Window(HINSTANCE hInstance, LPCWSTR name, DWORD style, int width, int height)
{
	main = this;

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

	//set size and check for error
	if (AdjustWindowRect(&size, style, false) == 0) {
		throw std::exception(Debug::TranslateHResult(GetLastError()).c_str());
	}

	// Create window
	hwnd = CreateWindow(name, name, style, CW_USEDEFAULT, CW_USEDEFAULT, size.right - size.left, size.bottom - size.top, NULL, NULL, hInstance, this);

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
}

Core::Window::~Window()
{
	DestroyWindow(hwnd);
}

float angle = 0.0f;

int Window::Run(void (*UpdateFunc)(void))
{
	int exitCode;

	/*Entity cam;
	Camera comp(&cam, Graphics::getWidth(), Graphics::getHeight());
	cam.addComponent(&comp);
	cam.transform.setPosition(0, 10, -10);
	cam.transform.setRotation(45, 0, 0);
	comp.fov = 60;*/

	/*Entity colourTest;
	colourTest.setParent(&cam);
	MeshRenderer* colourTestMesh = gfx.createMesh(&colourTest);
	colourTestMesh->getMesh()->ImportObj("assets/plane.obj");
	colourTest.transform.setScale(0.1f, 0.1f, 0.1f);
	colourTest.transform.setPosition(0, -1, 2);*/
	
	std::vector<Entity> Pntlights(20, Entity());

	srand(Time::getTime());
	
	for (int i = 0; i < 20; i++) {
		//Pntlights[i] = Entity();
		Vec3 pos = Vec3((std::rand() % 20) - 10, (float)(std::rand() % 100) * 0.05f, (std::rand() % 20) - 10);
		Vec3 col = Vec3((float)(std::rand() % 100) / 100, (float)(std::rand() % 100) / 100, (float)(std::rand() % 100) / 100);
		
		PointLight* pnt2 = gfx.createPointLight(&(Pntlights[i]));
		pnt2->Colour = col;

		Pntlights[i].transform.setScale(0.1f, 0.1f, 0.1f);
		Pntlights[i].transform.setPosition(pos);

		MeshRenderer* light2 = gfx.createMesh(&(Pntlights[i]));
		light2->getMesh()->ImportObj("assets/ssphere.obj");
		light2->getMaterial()->settings.color = { col.x, col.y, col.z, 1 };
		light2->getMaterial()->settings.glow = 1;
	}

	Entity cube1;
	gfx.createMesh(&cube1);
	cube1.transform.setPosition(0, 0, 0);
	cube1.getComponent<MeshRenderer>()->getMaterial()->settings.color = {1, 1, 1};// { 0, 1, 0.435f, 1 };

	Entity cube2;
	gfx.createMesh(&cube2);
	cube2.setParent(&cube1);
	cube2.transform.setPosition(-3, 0, 0);
	cube2.transform.setScale(0.5);
	cube2.getComponent<MeshRenderer>()->getMaterial()->settings.color = { 0, 0.6706f, 1, 1 };

	Entity floor;
	MeshRenderer* floorRend = gfx.createMesh(&floor);
	floorRend->getMesh()->ImportObj("assets/plane.obj");

	std::string skybox[6];
	skybox[0] = "assets/skybox/top.png";
	skybox[1] = "assets/skybox/bottom.png";
	skybox[2] = "assets/skybox/left.png";
	skybox[3] = "assets/skybox/right.png";
	skybox[4] = "assets/skybox/front.png";
	skybox[5] = "assets/skybox/back.png";
	gfx.setSkybox(skybox);

	//update to clear data during load time
	time.update();
	input.update();

	while (!WindowClosed(&exitCode))
	{
		//updates
		/*for (int i = 0; i < scripts.size(); i++)
			scripts[i]->Update();*/

		UpdateFunc();

		input.update();
		time.update();
		gfx.Draw();
		gfx.EndFrame();
	}
	return exitCode;
}

Graphics* Window::getGraphics()
{
	return &gfx;
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
		Debug::logErrorCode(DispatchMessage(&msg));
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
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
