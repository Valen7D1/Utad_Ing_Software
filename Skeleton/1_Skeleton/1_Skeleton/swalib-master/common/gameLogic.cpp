#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "ball.h"
#include "gameLogic.h"
#include "font.h"

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
	// Run balls
	for (int i = 0; i < NUM_BALLS; i++) {
		// New Pos.
		vec2 newpos = balls[i].getPosition() + balls[i].getVelocity();

		// Collision detection.
		bool collision = false;
		int colliding_ball = -1;
		for (int j = 0; j < NUM_BALLS; j++) {
			if (i != j) {
				float limit2 = (balls[i].getRadius() + balls[j].getRadius()) * (balls[i].getRadius() + balls[j].getRadius());
				if (vlen2(newpos - balls[j].getPosition()) <= limit2) {
					collision = true;
					colliding_ball = j;
					break;
				}
			}
		}

		if (!collision) {
			balls[i].setPosition(newpos);
		}
		else {
			// Rebound!
			balls[i].setVelocity(balls[i].getVelocity() * -1.f);
			balls[colliding_ball].setVelocity(balls[colliding_ball].getVelocity() * -1.f);
		}

		// Rebound on margins.
		if ((balls[i].getPosition().x > SCR_WIDTH) || (balls[i].getPosition().x < 0)) {
			balls[i].setVelocity(vec2(balls[i].getVelocity().x * -1.0, balls[i].getVelocity().y));
		}
		if ((balls[i].getPosition().y > SCR_HEIGHT) || (balls[i].getPosition().y < 0)) {
			balls[i].setVelocity(vec2(balls[i].getVelocity().x, balls[i].getVelocity().y * -1.0));
		}
	}
}