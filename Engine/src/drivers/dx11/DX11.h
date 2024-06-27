#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include <string>

#include "../../core/Logger.h"
#include "../../core/RLResult.h"

namespace rl
{
    std::string TranslateHResult(HRESULT code);
}

#define DX_THROW_ERROR(code) \
    if (FAILED(code))        \
    RL_THROW_EXCEPTION(rl::TranslateHResult(code).c_str())
#define DX_LOG_ERROR(code) \
    if (FAILED(code))      \
    RL_LOG_ERROR(rl::TranslateHResult(code).c_str())