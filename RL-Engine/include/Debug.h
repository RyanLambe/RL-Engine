#pragma once

#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <string>

static class Debug
{
public:

	static void start(bool debug);
	static void close();

	static void log(std::string out);
	static void logError(std::string out);
	static void logWarning(std::string out);
	static void logError(HRESULT code);

	static std::string TranslateHResult(HRESULT code);

private:

	//console
	static bool debugMode;
	static HANDLE hOut;

	//file logging
	static std::ofstream file;
};