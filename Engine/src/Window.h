#pragma once

#include "graphics/Renderer.h"
#include "Input.h"

#pragma comment(lib, "user32.lib")

namespace rl {
	class Window
	{
	public:
		
		Window(HINSTANCE hInstance, HWND parent, std::wstring name, DWORD style, int width, int height, bool debugMode);
		Window(const Window&) = delete;
		~Window();

		struct ExitCode {

			bool close = false;
			int exitCode;

		};

		ExitCode Run();

		//Graphics* getGraphics();
		static Window* main;

	private:
		bool WindowClosed(int* quitMessage);
		static LRESULT CALLBACK WindowProcThunk(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		HWND hwnd = nullptr;

		std::unique_ptr<Renderer> renderer;
		Input input;
		Clock time;
		Debug debug;
	};
}