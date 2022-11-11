#include "../include/CustomException.h"

CustomException::CustomException(int line, const char* file, std::string details, std::string type) : EngineException(line, file)
{
	this->details = details;
	this->type = type;
}

const char* CustomException::what() const
{
	outBuffer = details + "\n\n" + getLocation();
	return outBuffer.c_str();
}

const char* CustomException::GetType() const
{
	return type.c_str();
}
