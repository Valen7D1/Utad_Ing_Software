//inner includes
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "font.h"
//my includes
#include "gameLogic.h"
#include "manager.h"
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
	CORE_UnloadPNG(renderEngine->GetSprite()->getTexbkg());
	CORE_UnloadPNG(renderEngine->GetSprite()->getTexsmallball());
	FONT_End();
}


void LogicInitialization()
{
	// initialize every ball in balls from manager
	m_timer->InitTimer();
	manager->CreateGame();
}


// call to timer control and logic update
void LogicWorldSlot()
{
	m_timer->SetTimer();
	manager->update();
}
