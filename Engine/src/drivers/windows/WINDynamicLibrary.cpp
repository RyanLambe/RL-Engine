#include "WINDynamicLibrary.h"

namespace rl {
    WINDynamicLibrary::WINDynamicLibrary(const std::filesystem::path &file) {
        lib = LoadLibrary(file.string().c_str());

    }

    WINDynamicLibrary::~WINDynamicLibrary() {
        FreeLibrary(lib);
    }

    void *WINDynamicLibrary::GetFuncAddress(const std::string &name) {
        return (void*)GetProcAddress(lib, name.c_str());
    }

    u32 WINDynamicLibrary::GetLastErrorCode() {
        return (u32)GetLastError();
    }
}