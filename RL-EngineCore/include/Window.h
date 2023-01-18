#pragma once

#include "Graphics.h"
#include "Input.h"

#pragma comment(lib, "user32.lib")

namespace Core {
	class Window
	{
	public:
		
		Window(HINSTANCE hInstance, std::wstring name, DWORD style, int width, int height);
		Window(const Window&) = delete;
		~Window();

		struct ExitCode {

			bool close = false;
			int exitCode;

		};

		ExitCode Run();

		Graphics* getGraphics();
		static Window* main;

	private:
		bool WindowClosed(int* quitMessage);
		static LRESULT CALLBACK WindowProcThunk(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		HWND hwnd = nullptr;

		Graphics gfx;
		Input input;
		Time time;
		Debug debug;
	};
}