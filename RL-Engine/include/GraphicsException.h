#pragma once

#include <d3d11.h>
#include "EngineException.h"

#define GfxExcept(hr) GraphicsException(__LINE__, __FILE__, hr)
#define GfxThrowFailed(hr) if(FAILED(hr)) throw GraphicsException(__LINE__, __FILE__, hr)

class GraphicsException : public EngineException
{
public:
	GraphicsException(int line, const char* file, HRESULT hr);
	const char* what() const override;
	const char* GetType() const override;
	static std::string TranslateHResult(HRESULT hr);

private:
	HRESULT hr;
};

