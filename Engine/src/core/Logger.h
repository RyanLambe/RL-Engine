#pragma once

#include <iostream>

#include "Clock.h"

namespace rl::Logger
{

    template<typename T> void Log(const std::string& file, int line, const T& t)
    {
        std::cout << t << std::endl;
    }

    template<typename T, typename... Args> void Log(const std::string& file, int line, const T& t, const Args&... args)
    {
        std::cout << t;
        Log(file, line, args...);
    }

    // prints beginning of log
    template<typename... Args> void LogMessage(const std::string& file, int line, const Args&... args)
    {
        std::cout << "[LOG] [" << Clock::getFormattedTime() << "] [" << file << ":" << line << "] - ";
        Log(file, line, args...);
    }

    // prints beginning of log warning
    template<typename... Args> void LogWarning(const std::string& file, int line, const Args&... args)
    {
        std::cout << "[WARNING] [" << Clock::getFormattedTime() << "] [" << file << ":" << line << "] - ";
        Log(file, line, args...);
    }

    // prints beginning of log error
    template<typename... Args> void LogError(const std::string& file, int line, const Args&... args)
    {
        std::cout << "[ERROR] [" << Clock::getFormattedTime() << "] [" << file << ":" << line << "] - ";
        Log(file, line, args...);
    }

}

#define RL_LOG(...) rl::Logger::LogMessage(__FILE__, __LINE__, __VA_ARGS__)
#define RL_LOG_WARNING(...) rl::Logger::LogWarning(__FILE__, __LINE__, __VA_ARGS__)
#define RL_LOG_ERROR(...) rl::Logger::LogError(__FILE__, __LINE__, __VA_ARGS__)
