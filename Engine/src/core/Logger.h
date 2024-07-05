#pragma once

#include <sstream>
#include <utility>
#include <vector>

#include "Clock.h"

namespace rl
{
    class Logger
    {
    public:
        enum class LogType : uint8_t
        {
            Log = 0,
            Warning = 1,
            Error = 2
        };

        struct Message
        {
            LogType type;
            std::string message;
            std::string file;
            int line;
            std::string time;

            Message() = delete;
            Message(LogType type, std::string message, std::string file, int line) :
                type(type),
                message(std::move(message)),
                file(std::move(file)),
                line(line),
                time(Clock::getFormattedTime())
            {}

            [[nodiscard]] std::string GetFormatted() const
            {
                switch (type)
                {
                    case LogType::Log:
                        return "[LOG] [" + time + "] [" + file + ":" + std::to_string(line) + "]:\n" + message;
                    case LogType::Warning:
                        return "[WARNING] [" + time + "] [" + file + ":" + std::to_string(line) + "]:\n" + message;
                    case LogType::Error:
                        return "[ERROR] [" + time + "] [" + file + ":" + std::to_string(line) + "]:\n" + message;
                    default:
                        return "[UNKNOWN] [" + time + "] [" + file + ":" + std::to_string(line) + "]:\n" + message;
                }
            }
        };

        template<typename T> static void BuildMessage(std::ostringstream& ss, const T& t)
        {
            ss << t << "\n";
        }

        template<typename T, typename... Args>
        static void BuildMessage(std::ostringstream& ss, const T& t, const Args&... args)
        {
            ss << t;
            BuildMessage(ss, args...);
        }

        // creates log message
        template<typename... Args> static void LogMessage(const std::string& file, int line, const Args&... args)
        {
            std::ostringstream ss;
            BuildMessage(ss, args...);
            AddMessageInternal(LogType::Log, ss.str(), file, line);
        }

        // creates log warning
        template<typename... Args> static void LogWarning(const std::string& file, int line, const Args&... args)
        {
            std::ostringstream ss;
            BuildMessage(ss, args...);
            AddMessageInternal(LogType::Warning, ss.str(), file, line);
        }

        // creates log error
        template<typename... Args> static void LogError(const std::string& file, int line, const Args&... args)
        {
            std::ostringstream ss;
            BuildMessage(ss, args...);
            AddMessageInternal(LogType::Error, ss.str(), file, line);
        }

        [[nodiscard]] const std::vector<Message>& GetMessages() const
        {
            return messages;
        }

        void ClearMessages()
        {
            messages.clear();
        }

        void AddMessage(LogType type, const std::string& message, const std::string& file, int line)
        {
            messages.emplace_back(type, message, file, line);
        }

    private:
        std::vector<Message> messages = std::vector<Message>();

        static void AddMessageInternal(LogType type, const std::string& message, const std::string& file, int line);
    };
}

#define RL_LOG(...) rl::Logger::LogMessage(__FILE__, __LINE__, __VA_ARGS__)
#define RL_LOG_WARNING(...) rl::Logger::LogWarning(__FILE__, __LINE__, __VA_ARGS__)
#define RL_LOG_ERROR(...) rl::Logger::LogError(__FILE__, __LINE__, __VA_ARGS__)
