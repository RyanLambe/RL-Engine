#include "../pch.h"
#include "../include/ManagedWindow.h"

using namespace Engine;

ManagedWindow::ManagedWindow(HINSTANCE hInstance, LPCWSTR name, DWORD style, int width, int height) :
	Managed(new Core::Window(hInstance, name, style, width, height))
{

}

int ManagedWindow::Run(void (*UpdateFunc)(void)) {
	return instance->Run(UpdateFunc);
}
