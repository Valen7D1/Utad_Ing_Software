#pragma once
#include <Windows.h>


class Timer
{
public:
    Timer();

    //setters
    void SetTimer();

    //getters
    float GetFrameTime();
    double GetTotalTime();
    double GetTime_fps();
    double GetTotalFrameTime();
    double GetElapsed();

    void InitTimer(); // get starting values for frequency and actual time
    bool ProcessSlots(); // checker for logic loop
    void InitSlotsToProcess(); // calc all the new values

private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER actualTime;
    LARGE_INTEGER previousTime;

    // time control/render values
    double elapsedTime;
    double totalTime;
    double totalElapsed;
    double time_fps;
    double totalFrameTime;

    float frameTime = 1.0f / 60.0f; // Target time per frame for 60 fps
};

