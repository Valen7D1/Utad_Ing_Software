#pragma once
#include "stdafx.h"
#include "vector2d.h"

class SharedData {
public:
    void set_time_fps(double value);
    void set_totalTime(double value);
    void set_totalFrameTime(double value);

    double get_time_fps();
    double get_totalTime();
    double get_totalFrameTime();

private:
    double time_fps = 0;
    double totalTime = 0;
    double totalFrameTime = 0;
};