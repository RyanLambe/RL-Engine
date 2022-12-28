#include "../include/Time.h"

DWORD Time::startFrame;
DWORD Time::prevFrame;

std::vector<Time::Timer*> Time::timers;

void Time::start()
{
	//frames since start
	startFrame = GetTickCount64();
	update();
}

void Time::update()
{
	//frames since previous update
	prevFrame = GetTickCount64();
}

float Time::getTime()
{
	//get current frame
	DWORD curFrame = GetTickCount64();

	//get time since start in seconds
	return (float)(curFrame - startFrame) / 1000.0f;
}

float Time::deltaTime()
{
	//get current frame
	DWORD curFrame = GetTickCount64();

	//get frame since last frame in seconds
	return (float)(curFrame - prevFrame) / 1000.0f;
}

void Time::addTimer(Timer* timer)
{
	timers.push_back(timer);
}

void Time::Timer::start()
{
	addTimer(this);
	startFrame = GetTickCount64();
}

float Time::Timer::getTime()
{
	//get current frame
	DWORD curFrame = GetTickCount64();

	//get time since start in seconds
	return (float)(curFrame - startFrame) / 1000.0f;
}
