
//#include <SceneManager.h>
#include <core/Application.h>

using namespace rl;

int main(){
    Application application;
    application.Run();
}

/*int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	std::wstring test = L"name";
	Window window(hInstance, nullptr, test, WS_OVERLAPPEDWINDOW, 1280, 720, true);
	//SceneManager::Scene* scene = SceneManager::CreateScene();

	Window::ExitCode exitCode = window.Run();
	while(!exitCode.close)
	{
		exitCode = window.Run();
	}

    return exitCode.exitCode;
}*/