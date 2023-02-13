#include "../include/Application.h"

Engine::Application::Application(System::String^ name, int width, int height, bool debugMode)
{
	//get hInstance
	HINSTANCE hInstance = (HINSTANCE)System::Runtime::InteropServices::Marshal::GetHINSTANCE(System::Reflection::Assembly::GetExecutingAssembly()->GetModules()[0]).ToPointer();

	//turn name to correct type
	std::wstring wName = msclr::interop::marshal_as<std::wstring>(name);

	//run
	instance = new Core::Window(hInstance, wName, WS_OVERLAPPEDWINDOW, width, height, debugMode);
}

Engine::Application::~Application() {
	if (instance)
		delete instance;
}

Engine::Application::!Application() {
	if (instance)
		delete instance;
}

int Engine::Application::Run(array<Script^>^ scripts)
{
	if (instance == nullptr)
		return -1;

	//start
	for (int i = 0; i < scripts->Length; i++)
		scripts[i]->Start();

	//every frame
	while (!WindowClosed(instance->Run())) {
		for (int i = 0; i < scripts->Length; i++)
			scripts[i]->Update();
	}
		
	return exitCode;
}

void Engine::Application::Close()
{
	close = true;
}

void Engine::Application::SetFullscreen(bool fullscreen)
{
	Core::Window::main->getGraphics()->setFullscreen(fullscreen);
}

bool Engine::Application::WindowClosed(Core::Window::ExitCode exitCode)
{
	this->exitCode = exitCode.exitCode;
	return exitCode.close || this->close;
}
