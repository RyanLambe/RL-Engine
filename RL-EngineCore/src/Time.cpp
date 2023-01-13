#include "../include/Time.h"

DWORD Core::Time::startFrame;
DWORD Core::Time::prevFrame;

std::vector<Core::Time::Timer*> Core::Time::timers;

Core::Time::Time()
{
	//frames since start
	startFrame = GetTickCount64();
	update();
}

void Core::Time::update()
{
	//frames since previous update
	prevFrame = GetTickCount64();
}

float Core::Time::getTime()
{
	//get current frame
	DWORD curFrame = GetTickCount64();

	//get time since start in seconds
	return (float)(curFrame - startFrame) / 1000.0f;
}

float Core::Time::deltaTime()
{
	//get current frame
	DWORD curFrame = GetTickCount64();

	//get frame since last frame in seconds
	return (float)(curFrame - prevFrame) / 1000.0f;
}

void Core::Time::addTimer(Timer* timer)
{
	timers.push_back(timer);
}

void Core::Time::Timer::start()
{
	addTimer(this);
	startFrame = GetTickCount64();
}

float Core::Time::Timer::getTime()
{
	//get current frame
	DWORD curFrame = GetTickCount64();

	//get time since start in seconds
	return (float)(curFrame - startFrame) / 1000.0f;
}
