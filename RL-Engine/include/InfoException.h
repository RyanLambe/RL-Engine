#pragma once

#include "GraphicsException.h"

#include <vector>

#define InfoThrowFailed(hr) infoManager.Set(); if(FAILED(HRESULT h = (hr))) {throw GfxExcept(h)}
#define InfoThrowInfoOnly(hr) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if(!v.empty()) {throw InfoException(__LINE__, __FILE__, v)}}

class InfoException : public EngineException
{
public:
	InfoException(int line, const char* file, std::vector<std::string> infoMsgs);
	const char* what() const override;
	const char* GetType() const override;
	std::string GetErrorInfo() const;

private:
	std::string info;
};