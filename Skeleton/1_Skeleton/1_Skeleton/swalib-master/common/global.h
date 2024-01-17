#pragma once
#include "stdafx.h"
#include "vector2d.h"

const unsigned int NUM_BALLS = 10;  // Max. num balls.
const float MAX_BALL_SPEED = 480.0f;   // Max vel. of ball (pixels/?).


struct Ball	// Info Ball
{
	vec2   pos;	// Position.
	vec2   vel;	// Velocity.
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	float  radius;	// Radius.

	Ball();
};

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