#pragma once

#include <sstream>
#include <stdexcept>
#include <utility>

#include "Logger.h"

namespace rl{

    // error code is the type of errors that can happen regular use
    enum ErrorCode {
        Success = 0,
        UnknownError = 1,
        InvalidArguments = 2,
        Unimplemented = 3,
        FileNotFound = 4,
    };

    // RLResult will be returned by functions that have a chance of failure
    struct RLResult{
        ErrorCode code;

        RLResult() = delete;
        explicit RLResult(ErrorCode code): code(code) {}

        [[nodiscard]]
        inline bool Failed() const noexcept{
            return code != Success;
        }

        [[nodiscard]]
        inline std::string toString() const noexcept{
            switch (code) {
                case Success: return "Success";
                case UnknownError: return "Unknown Error";
                case InvalidArguments: return "Invalid Arguments";
                case Unimplemented: return "Unimplemented";
                case FileNotFound: return "File Not Found";
                default: return "Invalid Error Type";
            }
        }
    };

    // when a critical error occurs the RLException will be thrown
    class RLException : public std::exception{
    public:
        RLException(std::string  msg, std::string  file, int line) {
            std::ostringstream oss;

            oss << "Program Exited with Error: \n" << msg << "\n\n";
            oss << "File: " << file << "\nLine: " << line;

            message = oss.str();
        }

        [[nodiscard]]
        const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}

#define RL_THROW_EXCEPTION(msg) throw RLException(msg, __FILE__, __LINE__)
#define RL_THROW_RESULT(res) throw RLException(res.toString(), __FILE__, __LINE__)
#define RL_CHECK_RESULT(res) if(res.Failed()) throw RLException(res.toString(), __FILE__, __LINE__)
#define RL_PRINT_RESULT(res) if(res.Failed()) RL_LOG_ERROR("Error: ", res.toString())

