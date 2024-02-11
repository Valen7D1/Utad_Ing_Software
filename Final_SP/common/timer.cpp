#include "timer.h"


// constructor
Timer::Timer() : elapsedTime(0), totalTime(0), totalElapsed(0), time_fps(0), totalFrameTime(0),
	frameTime(1.0f / 60.0f) // Target time per frame for 60 fps
	{}


// get all the variables needed for timer control
void Timer::SetTimer() {
	totalFrameTime += frameTime;
	time_fps = totalElapsed;
	totalElapsed -= frameTime;
}


//get time values
void Timer::InitSlotsToProcess()
{
	// get current time and extract elapsed
	QueryPerformanceCounter(&actualTime);
	elapsedTime = (static_cast<double>(actualTime.QuadPart) - static_cast<double>(previousTime.QuadPart)) / static_cast<double>(frequency.QuadPart);
	previousTime = actualTime;

	// set variables for time render and timer control
	totalTime += elapsedTime;
	totalElapsed += elapsedTime;

	// time chaos void control
	if (totalElapsed > 1.0 / 15.0)
	{
		totalElapsed = 1.0 / 15.0;
	}
}


bool Timer::ProcessSlots() 
{
	return totalElapsed >= frameTime;
}


// TOCHECK (should be instead in constructor?)
void Timer::InitTimer()
{
	QueryPerformanceCounter(&previousTime);
	QueryPerformanceFrequency(&frequency);
}


float Timer::GetFrameTime() { return frameTime; }

double Timer::GetTotalTime() { return totalTime; }

double Timer::GetTime_fps() { return time_fps; }

double Timer::GetTotalFrameTime() { return totalFrameTime; }

double Timer::GetElapsed() { return elapsedTime; }