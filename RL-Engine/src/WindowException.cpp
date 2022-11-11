#include "../include/WindowException.h"

WindowException::WindowException(int line, const char* file, HRESULT hr) : EngineException(line, file)
{
	this->hr = hr;
}

const char* WindowException::what() const
{
	outBuffer = TranslateHResult(hr) + "\n" + getLocation();
	return outBuffer.c_str();
}

const char* WindowException::GetType() const
{
	return "Window Exception";
}

std::string WindowException::TranslateHResult(HRESULT hr)
{
	//reformat message
	char* msgBuffer = nullptr;
	DWORD msgLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&msgBuffer), 0, nullptr);

	//check if there is a message
	if (msgLength == 0)
		return "Unknown Exception";

	//return
	std::string out = msgBuffer;
	LocalFree(msgBuffer);
	return out;
}