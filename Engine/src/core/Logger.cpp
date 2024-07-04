#include "Logger.h"

#include "Application.h"

namespace rl
{
    void Logger::AddMessageInternal(Logger::LogType type, const std::string& message, const std::string& file, int line)
    {
        Application::GetLogger().AddMessage(type, message, file, line);
    }
}