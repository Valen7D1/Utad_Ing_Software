#include "global.h"


GLuint texbkg;
GLuint texsmallball;

Ball::Ball() : pos(0.0f), vel(0.0f), gfx(0), radius(0.0f)
{}

double SharedData::get_time_fps() {
	return time_fps;
}

double SharedData::get_totalTime() {
	return totalTime;
}

double SharedData::get_totalFrameTime() {
	return totalFrameTime;
}

void SharedData::set_time_fps(double value) {
	time_fps = value;
}

void SharedData::set_totalTime(double value) {
	totalTime = value;
}

void SharedData::set_totalFrameTime(double value) {
	totalFrameTime = value;
}
