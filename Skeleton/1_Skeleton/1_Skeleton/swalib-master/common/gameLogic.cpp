#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "ball.h"
#include "gameLogic.h"
#include "font.h"
#include "global.h"

int frames;
Ball balls[NUM_BALLS];
extern GLuint texbkg;
extern GLuint texsmallball;

//Variables para el control del tiempo
LARGE_INTEGER frequency;
LARGE_INTEGER actualTime;
LARGE_INTEGER previousTime;

double elapsedTime = 0;
double totalTime = 0;
double totalElapsed = 0;
double time_fps = 0;
double totalFrameTime = 0;

float frameTime = 1.0f / 60.0f; // Target time per frame for 60 fps

//SharedData sharedData;

void timeControl()
{
	QueryPerformanceCounter(&actualTime);
	elapsedTime = (static_cast<double>(actualTime.QuadPart) - static_cast<double>(previousTime.QuadPart)) / static_cast<double>(frequency.QuadPart);
	previousTime = actualTime;

	totalTime += elapsedTime;
	totalElapsed += elapsedTime;

	if (totalElapsed > 1.0 / 15.0)
	{
		totalElapsed = 1.0 / 15.0;
	}
	while (totalElapsed >= frameTime)
	{
		ProcessGameLogic();
		totalFrameTime += frameTime;
		time_fps = totalElapsed;
		totalElapsed -= frameTime;
	}
	//SYS_Sleep(50);
}


void Shutdown()
{
	// Unload textures.
	CORE_UnloadPNG(texbkg);
	CORE_UnloadPNG(texsmallball);
	FONT_End();
}

void LogicInitialization()
{
	QueryPerformanceCounter(&previousTime);
	QueryPerformanceFrequency(&frequency);

	// Init game state.
	for (int i = 0; i < NUM_BALLS; i++) {
		balls[i].setPosition(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
		balls[i].setVelocity(vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED) * frameTime, CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED) * frameTime));
		balls[i].setRadius(16.f);
		balls[i].gfx = texsmallball;
	}
}



void ProcessGameLogic()
{
	Manager::update();
}