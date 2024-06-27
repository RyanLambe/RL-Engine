#include "dx11.h"

std::string rl::TranslateHResult(HRESULT code)
{
    // reformat message
    char *msgBuffer = nullptr;
    DWORD msgLength = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, code,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&msgBuffer), 0, nullptr);

    // check if there is a message
    if (msgLength == 0)
        return "Unknown Exception";

    // return
    std::string out = msgBuffer;
    LocalFree(msgBuffer);
    return out;
}
