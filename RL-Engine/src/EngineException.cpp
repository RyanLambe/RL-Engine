#include "../include/EngineException.h"

EngineException::EngineException(int line, const char* file)
{
	this->line = line;
	this->file = file;
}

const char* EngineException::what() const
{
	std::ostringstream oss;
	oss << "Exception: " << GetType() << "\n" << getLocation();
	outBuffer = oss.str();
	return outBuffer.c_str();
}

const char* EngineException::GetType() const
{
	return "Engine Exception";
}

std::string EngineException::getLocation() const
{
	return "File: " + file + ", Line: " + std::to_string(line);
}
