#include "../include/Debug.h"

bool Debug::debugMode;
HANDLE Debug::hOut;

std::ofstream Debug::file;

void Debug::start(bool debug)
{
    debugMode = debug;
    if (debugMode) {
        //setup console
        AllocConsole();
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        //setup font
        CONSOLE_FONT_INFOEX font = {};
        font.cbSize = sizeof(font);
        font.dwFontSize.Y = 24;
        font.FontWeight = FW_NORMAL;
        wcscpy_s(font.FaceName, L"Consolas");
        SetCurrentConsoleFontEx(hOut, false, &font);
    }

    //file logging
    file.open("log.txt", std::ios::trunc);
}

void Debug::close()
{
    if(debugMode)
        FreeConsole();
    file.close();
}

void Debug::log(std::string out)
{
    //line to be written
    std::string line = "INFO [time]: " + out + "\n";

    //write to console
    if (debugMode) {
        //set correct font
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //print to console
        WriteConsoleA(hOut, line.c_str(), line.size(), nullptr, nullptr);
    }
    
    //file logging
    file << line;
}

void Debug::logError(std::string out)
{
    //line to be written
    std::string line = "ERROR [time]: " + out + "\n";

    //write to console
    if (debugMode) {
        //set correct font
        SetConsoleTextAttribute(hOut, FOREGROUND_RED);

        //print to console
        WriteConsoleA(hOut, line.c_str(), line.size(), nullptr, nullptr);
    }
    
    //file logging
    file << line;
}

void Debug::logWarning(std::string out)
{
    //line to be written
    std::string line = "WARNING [time]: " + out + "\n";

    //write to console
    if (debugMode) {
        //set correct font
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);

        //print to console
        WriteConsoleA(hOut, line.c_str(), line.size(), nullptr, nullptr);
    }

    //file logging
    file << line;
}

void Debug::logError(HRESULT code)
{
    if (FAILED(code)) 
        logError(TranslateHResult(code));
}

std::string Debug::TranslateHResult(HRESULT code)
{
    //reformat message
    char* msgBuffer = nullptr;
    DWORD msgLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&msgBuffer), 0, nullptr);

    //check if there is a message
    if (msgLength == 0)
        return "Unknown Exception";

    //return
    std::string out = msgBuffer;
    LocalFree(msgBuffer);
    return out;
}