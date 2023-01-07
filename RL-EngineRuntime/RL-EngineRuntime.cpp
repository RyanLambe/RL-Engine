#include "pch.h"

#include <msclr/marshal_cppstd.h>
#include "ScriptManager.h"

using namespace System;

int main()
{
	try {
		//setup
		HINSTANCE hInstance = (HINSTANCE)Runtime::InteropServices::Marshal::GetHINSTANCE(Reflection::Assembly::GetExecutingAssembly()->GetModules()[0]).ToPointer();
		Engine::ManagedWindow^ window = gcnew Engine::ManagedWindow(hInstance, L"RL-Engine", WS_OVERLAPPEDWINDOW, 1280, 720);

		//ScriptManager scripts;
		//Engine::Entity^ ent = gcnew Engine::Entity();
		//scripts.test = gcnew Test(ent);

		//run
		int out = window->Run(UpdateScripts);

		//close
		return out;
	}
	catch (std::exception& e) {
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) {
		MessageBoxA(nullptr, "Check log file for more info.", "Error", MB_OK | MB_ICONEXCLAMATION);
	}

	//didnt return in try therefore error
	return -1;
}