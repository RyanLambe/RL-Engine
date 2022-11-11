#pragma once

#include <Windows.h>
#include "EngineException.h"

#define WndExcept(hr) WindowException(__LINE__, __FILE__, hr)
#define WndThrowFailed(hr) if(FAILED(hr)) throw WindowException(__LINE__, __FILE__, hr)

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