#pragma once

#include "EngineException.h"

#define CustomExceptSimple(details) CustomException(__LINE__, __FILE__, details, "Custom Exception")
#define CustomExcept(details, type) CustomException(__LINE__, __FILE__, details, type)

class CustomException : public EngineException
{
public:
	CustomException(int line, const char* file, std::string details, std::string type);
	const char* what() const override;
	const char* GetType() const override;

private:
	std::string details;
	std::string type;
};

