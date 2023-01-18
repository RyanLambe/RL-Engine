#include "../include/ManagedWindow.h"

Engine::ManagedWindow::ManagedWindow(System::String^ name, int width, int height) : Managed(nullptr)
{
	//get hInstance
	HINSTANCE hInstance = (HINSTANCE)System::Runtime::InteropServices::Marshal::GetHINSTANCE(System::Reflection::Assembly::GetExecutingAssembly()->GetModules()[0]).ToPointer();

	//turn name to correct type
	std::wstring wName = msclr::interop::marshal_as<std::wstring>(name);

	//run
	instance = new Core::Window(hInstance, wName, WS_OVERLAPPEDWINDOW, width, height);
}

int Engine::ManagedWindow::Run(array<Script^>^ scripts)
{
	if (instance == nullptr)
		return -1;
	while (!WindowClosed(instance->Run())) {
		for (int i = 0; i < scripts->Length; i++)
			scripts[i]->Update();
	}
		
	return exitCode;
}

void Engine::ManagedWindow::Close()
{
	close = true;
}

void Engine::ManagedWindow::SetFullscreen(bool fullscreen)
{
	Core::Graphics::setFullscreen(fullscreen);
}

bool Engine::ManagedWindow::WindowClosed(Core::Window::ExitCode exitCode)
{
	this->exitCode = exitCode.exitCode;
	return exitCode.close || this->close;
}
