#include "DynamicLibrary.h"

#ifdef RL_USE_WINDOWS
#include "../drivers/windows/WINDynamicLibrary.h"
#endif

namespace rl {

    std::shared_ptr<DynamicLibrary> DynamicLibrary::Load(const std::filesystem::path &file) {

        #ifdef RL_USE_WINDOWS
        return std::make_shared<WINDynamicLibrary>(file);
        #endif

        RL_THROW_EXCEPTION("No System Driver has been specified. unable to create dynamic library");
    }
}