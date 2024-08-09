#pragma once

#include <memory>
#include <vector>
#include <filesystem>
#include <any>

#include "RLResult.h"
#include "../types/Types.h"

namespace rl {
    class DynamicLibrary {
    public:
        virtual ~DynamicLibrary() = default;

        static std::shared_ptr<DynamicLibrary> Load(const std::filesystem::path& file);

        template<typename T, typename... Args>
        T RunFunction(const std::string& name, const Args&... args)
        {
            typedef T (*FuncType)(const Args&... args);
            auto func = (FuncType)GetFuncAddress(name);
            if (!func)
            {
                RL_LOG_ERROR(name, " function not found: ", GetLastErrorCode());
                return T();
            }

            try
            {
                return func(args...);
            }
            catch (const std::exception& e)
            {
                RL_LOG_ERROR(e.what());
            }
            catch (...)
            {
                RL_LOG_ERROR("Caught Unknown Exception");
            }
            return T();
        }

        template<typename T, typename... Args>
        T RunFunctionVal(const std::string& name, Args... args)
        {
            typedef T (*FuncType)(Args... args);
            auto func = (FuncType)GetFuncAddress(name);
            if (!func)
            {
                RL_LOG_ERROR(name, " function not found: ", GetLastErrorCode());
                return T();
            }

            try
            {
                return func(args...);
            }
            catch (const std::exception& e)
            {
                RL_LOG_ERROR(e.what());
            }
            catch (...)
            {
                RL_LOG_ERROR("Caught Unknown Exception");
            }
            return T();
        }

    protected:
        virtual void* GetFuncAddress(const std::string& name) = 0;
        virtual u32 GetLastErrorCode() = 0;
    };
}
