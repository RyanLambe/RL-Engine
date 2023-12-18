#pragma once

#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <string>

#include "Time.h"
#include "types/Vec2.h"
#include "types/Vec3.h"

namespace rl {
	class Debug
	{
	public:

		void start(bool debug);
		~Debug();

		static void log(std::string out);
		static void log(char out[]);
		static void log(const char out[]);
		static void log(int out);
		static void log(unsigned int out);
		static void log(float out);
		static void log(long out);
		static void log(double out);
		static void log(long long out);
		static void log(long double out);
		static void log(unsigned long out);
		static void log(unsigned long long out);
		static void log(bool out);
		static void log(Vec2 out);
		static void log(Vec3 out);

		static void logError(std::string out);
		static void logError(char out[]);
		static void logError(const char out[]);
		static void logError(int out);
		static void logError(unsigned int out);
		static void logError(float out);
		static void logError(long out);
		static void logError(double out);
		static void logError(long long out);
		static void logError(long double out);
		static void logError(unsigned long out);
		static void logError(unsigned long long out);
		static void logError(bool out);
		static void logError(Vec2 out);
		static void logError(Vec3 out);
		static void logErrorCode(HRESULT code);


		static void logWarning(std::string out);
		static void logWarning(char out[]);
		static void logWarning(const char out[]);
		static void logWarning(int out);
		static void logWarning(unsigned int out);
		static void logWarning(float out);
		static void logWarning(long out);
		static void logWarning(double out);
		static void logWarning(long long out);
		static void logWarning(long double out);
		static void logWarning(unsigned long out);
		static void logWarning(unsigned long long out);
		static void logWarning(bool out);
		static void logWarning(Vec2 out);
		static void logWarning(Vec3 out);

		static std::string TranslateHResult(HRESULT code);

	private:

		//gets time as "[mins:secs]: "
		static std::string formatedTime();
		static void print(std::string out, WORD colour);

		//console
		static bool debugMode;
		static HANDLE hOut;

		//file logging
		static std::ofstream file;
	};
}