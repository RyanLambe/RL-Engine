#pragma once
#include <Windows.h>

#include "EngineException.h"
#include "Graphics.h"

class Window
{
public:
	Window(HINSTANCE hInstance, LPCWSTR name, DWORD style, int width, int height);
	~Window();

	int Run();

private:
	bool WindowClosed(int* quitMessage);
	static LRESULT CALLBACK WindowProcThunk(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND hwnd;
	Graphics gfx;

//Window Exception
public:
	class WindowException : public EngineException
	{
	public:
		WindowException(int line, const char* file, HRESULT hr);
		const char* what() const override;
		const char* GetType() const override;
		static std::string TranslateHResult(HRESULT hr);

	private:
		HRESULT hr;
	};
};

//Exception macro
#define EXCEPT(hr) Window::WindowException(__LINE__, __FILE__, hr)