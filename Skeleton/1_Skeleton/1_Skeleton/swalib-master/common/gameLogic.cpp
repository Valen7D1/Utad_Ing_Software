//inner includes
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "font.h"
//my includes
#include "ball.h"
#include "gameLogic.h"
#include "global.h"

extern GLuint texbkg;
extern GLuint texsmallball;

Manager* manager = Manager::getInstance();
Timer* m_timer = manager->getTimer();

void LogicSlot()
{
	m_timer->InitSlotsToProcess();
	while (m_timer->ProcessSlots())
	{
		LogicWorldSlot();
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
	m_timer->InitTimer();

	std::vector<Ball>* balls = manager->getBalls();

	for (Ball& ball : *balls) {
	// Init game state.
		ball.setPosition(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
		ball.setVelocity(vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED) * m_timer->GetFrameTime(), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED) * m_timer->GetFrameTime()));
		ball.setRadius(16.f);
		ball.gfx = texsmallball;
	}
}


void Timer::SetTimer() {
	totalFrameTime += frameTime;
	time_fps = totalElapsed;
	totalElapsed -= frameTime;
}


void LogicWorldSlot()
{
	m_timer->SetTimer();
	manager->update();
}


void Timer::InitSlotsToProcess()
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
}


bool Timer::ProcessSlots() 
{
	return totalElapsed >= frameTime;
}


void Timer::InitTimer()
{
	QueryPerformanceCounter(&previousTime);
	QueryPerformanceFrequency(&frequency);
}

float Timer::GetFrameTime() { return frameTime; }

double Timer::GetTotalTime() { return totalTime; }

double Timer::GetTime_fps() { return time_fps; }

double Timer::GetTotalFrameTime() { return totalFrameTime; }