#pragma once
#include <exception>
#include <string>
#include <sstream>

class EngineException : public std::exception
{
public:
	EngineException(int line, const char* file);
	const char* what() const override;
	virtual const char* GetType() const;
	std::string getLocation() const;

private:
	int line;
	std::string file;

protected:
	mutable std::string outBuffer;
};

