#pragma once

#include "../../core/DynamicLibrary.h"

#define NOMINMAX
#include <windows.h>

namespace rl {
    class WINDynamicLibrary : public DynamicLibrary{

    public:
        WINDynamicLibrary() = delete;
        WINDynamicLibrary(const std::filesystem::path& file);
        ~WINDynamicLibrary() override;

        void* GetFuncAddress(const std::string &name) override;
        u32 GetLastErrorCode() override;

    private:
        HINSTANCE lib = nullptr;
    };
}
