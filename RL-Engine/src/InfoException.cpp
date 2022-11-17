#include "../include/InfoException.h"


InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) : EngineException(line, file) {
	for (auto& m : infoMsgs) {
		info += m;
		info.push_back('\n');
	}
	if (!info.empty())
		info.pop_back();
}

const char* InfoException::what() const
{
	outBuffer = GetErrorInfo() + "\n" + getLocation();
	return outBuffer.c_str();
}

const char* InfoException::GetType() const
{
	return "Info Exception";
}

std::string InfoException::GetErrorInfo() const {
	return info;
}