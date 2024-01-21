//inner includes
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "font.h"
//my includes
#include "ball.h"
#include "gameLogic.h"
#include "global.h"
#include "renderEngine.h"


// get manager and timer
Manager* manager = Manager::getInstance();
Timer* m_timer = manager->getTimer();

RenderEngine* renderEngine = RenderEngine::getInstance();


void LogicSlot()
{
	// time control
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
	CORE_UnloadPNG(renderEngine->texbkg);
	CORE_UnloadPNG(renderEngine->texsmallball);
	FONT_End();
}


void LogicInitialization()
{
	// initialize every ball in balls from manager
	m_timer->InitTimer();

	std::vector<Ball>* balls = manager->getBalls();

	for (Ball& ball : *balls) {
	// Init game state.
		ball.setPosition(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));
		ball.setVelocity(vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED) * m_timer->GetFrameTime(), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED) * m_timer->GetFrameTime()));
		ball.setRadius(16.f);
		ball.gfx = renderEngine->texsmallball;
	}
}


// call to timer control and logic update
void LogicWorldSlot()
{
	m_timer->SetTimer();
	manager->update();
}
