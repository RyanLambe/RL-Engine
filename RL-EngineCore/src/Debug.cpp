#include "../include/Debug.h"

using namespace Core;

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

Debug::~Debug()
{
    if (debugMode)
        FreeConsole();
    file.close();
}

//logs
void Debug::log(std::string out)
{
    std::string line = "INFO " + formatedTime() + out + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(char out[])
{
    std::string line = "INFO " + formatedTime() + out + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(const char out[])
{
    std::string line = "INFO " + formatedTime() + out + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(int out)
{
    std::string line = "INFO " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(unsigned int out)
{
    std::string line = "INFO " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(float out)
{
    std::string line = "INFO " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(long out)
{
    std::string line = "INFO " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(double out)
{
    std::string line = "INFO " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(long long out)
{
    std::string line = "INFO " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(long double out)
{
    std::string line = "INFO " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(unsigned long out)
{
    std::string line = "INFO " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(unsigned long long out)
{
    std::string line = "INFO " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(bool out)
{
    std::string line;
    if(out)
        line = "INFO " + formatedTime() + "True" + "\n";
    else
        line = "INFO " + formatedTime() + "False" + "\n";

    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(Vec2 out)
{
    std::string line = "INFO " + formatedTime();
    line += "x: " + std::to_string(out.x);
    line += ", y: " + std::to_string(out.y) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Debug::log(Vec3 out)
{
    std::string line = "INFO " + formatedTime();
    line += "x: " + std::to_string(out.x);
    line += ", y: " + std::to_string(out.y);
    line += ", z: " + std::to_string(out.z) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//errors
void Debug::logError(std::string out)
{
    std::string line = "ERROR " + formatedTime() + out + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(char out[])
{
    std::string line = "ERROR " + formatedTime() + out + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(const char out[])
{
    std::string line = "ERROR " + formatedTime() + out + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(int out)
{
    std::string line = "ERROR " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(unsigned int out)
{
    std::string line = "ERROR " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(float out)
{
    std::string line = "ERROR " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(long out)
{
    std::string line = "ERROR " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(double out)
{
    std::string line = "ERROR " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(long long out)
{
    std::string line = "ERROR " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(long double out)
{
    std::string line = "ERROR " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(unsigned long out)
{
    std::string line = "ERROR " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(unsigned long long out)
{
    std::string line = "ERROR " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED);
}

void Debug::logError(bool out)
{
    std::string line;
    if (out)
        line = "ERROR " + formatedTime() + "True" + "\n";
    else
        line = "ERROR " + formatedTime() + "False" + "\n";

    print(line, FOREGROUND_RED);
}

void Debug::logErrorCode(HRESULT code)
{
    if (FAILED(code))
        logError(TranslateHResult(code));
}

//warnings
void Debug::logWarning(std::string out)
{
    std::string line = "WARNING " + formatedTime() + out + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(char out[])
{
    std::string line = "WARNING " + formatedTime() + out + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(const char out[])
{
    std::string line = "WARNING " + formatedTime() + out + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(int out)
{
    std::string line = "WARNING " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(unsigned int out)
{
    std::string line = "WARNING " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(float out)
{
    std::string line = "WARNING " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(long out)
{
    std::string line = "WARNING " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(double out)
{
    std::string line = "WARNING " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(long long out)
{
    std::string line = "WARNING " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(long double out)
{
    std::string line = "WARNING " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(unsigned long out)
{
    std::string line = "WARNING " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(unsigned long long out)
{
    std::string line = "WARNING " + formatedTime() + std::to_string(out) + "\n";
    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Debug::logWarning(bool out)
{
    std::string line;
    if (out)
        line = "WARNING " + formatedTime() + "True" + "\n";
    else
        line = "WARNING " + formatedTime() + "False" + "\n";

    print(line, FOREGROUND_RED | FOREGROUND_GREEN);
}


//helper functions
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

std::string Debug::formatedTime()
{
    //get values
    int secs = Time::getTime();
    int mins = floor(secs / 60);
    secs -= mins * 60;

    //format string
    std::string out = "[";
    out += std::to_string(mins);
    out += ":";

    //make seconds 2 digits
    if (secs < 10)
        out += "0";

    out += std::to_string(secs);
    out += "]: ";

    //return
    return out;
}

void Debug::print(std::string out, WORD colour)
{
    //write to console
    if (true) {
        //set correct font
        SetConsoleTextAttribute(hOut, colour);

        //print to console
        WriteConsoleA(hOut, out.c_str(), out.size(), nullptr, nullptr);
    }

    //file logging
    file << out;
}