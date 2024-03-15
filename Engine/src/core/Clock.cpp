#include "Clock.h"

#include <chrono>

using namespace rl;

std::string Clock::getFormattedTime(){
    std::time_t time = std::time(nullptr);
    std::tm* local_time = std::localtime(&time);

    std::stringstream ss;
    ss << local_time->tm_hour << ":" << local_time->tm_min << ":" << local_time->tm_sec;
    return ss.str();
}