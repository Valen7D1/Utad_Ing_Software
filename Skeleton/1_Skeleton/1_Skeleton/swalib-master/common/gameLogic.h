#pragma once
#include <Windows.h>

void LogicSlot();
void LogicInitialization();
void LogicWorldSlot();
void Shutdown();


class Timer
{
public:

    void SetTimer();
    void InitTimer();
    bool ProcessSlots();
    void InitSlotsToProcess();

    float GetFrameTime();
    double GetTotalTime();
    double GetTime_fps();
    double GetTotalFrameTime();

private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER actualTime;
    LARGE_INTEGER previousTime;

    int frames;

    double elapsedTime = 0;
    double totalTime = 0;
    double totalElapsed = 0;
    double time_fps = 0;
    double totalFrameTime = 0;

    float frameTime = 1.0f / 60.0f; // Target time per frame for 60 fps
};

