#include "Clock.h"

using namespace rl;

DWORD Clock::startFrame;
DWORD Clock::prevFrame;

std::vector<Clock::Timer*> Clock::timers;

Clock::Clock()
{
	//frames since start
	startFrame = GetTickCount64();
	update();
}

void Clock::update()
{
	//frames since previous update
	prevFrame = GetTickCount64();
}

float Clock::getTime()
{
	//get current frame
	DWORD curFrame = GetTickCount64();

	//get time since start in seconds
	return (float)(curFrame - startFrame) / 1000.0f;
}

float Clock::deltaTime()
{
	//get current frame
	DWORD curFrame = GetTickCount64();

	//get frame since last frame in seconds
	return (float)(curFrame - prevFrame) / 1000.0f;
}

void Clock::addTimer(Timer* timer)
{
	timers.push_back(timer);
}

void Clock::Timer::start()
{
	addTimer(this);
	startFrame = GetTickCount64();
}

float Clock::Timer::getTime()
{
	//get current frame
	DWORD curFrame = GetTickCount64();

	//get time since start in seconds
	return (float)(curFrame - startFrame) / 1000.0f;
}
