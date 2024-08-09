#include "WINDynamicLibrary.h"

namespace rl {
    WINDynamicLibrary::WINDynamicLibrary(const std::filesystem::path &file) {
        lib = LoadLibrary(file.string().c_str());
        if (!lib)
        {
            RL_LOG_ERROR(GetLastError(), " - unable to link to library: ", file.string());
            return;
        }
        RL_LOG_WARNING("Game.dll Connected.");
    }

    WINDynamicLibrary::~WINDynamicLibrary() {
        RL_LOG_WARNING("Disconnected from library");
        FreeLibrary(lib);
    }

    void *WINDynamicLibrary::GetFuncAddress(const std::string &name) {
        return (void*)GetProcAddress(lib, name.c_str());
    }

    u32 WINDynamicLibrary::GetLastErrorCode() {
        return (u32)GetLastError();
    }
}