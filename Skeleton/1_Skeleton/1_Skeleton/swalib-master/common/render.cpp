//inner includes
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
//my includes
#include "render.h"
#include "global.h"
#include "gameLogic.h"
#include "renderEngine.h"


RenderEngine* render = RenderEngine::getInstance();


void RenderInitialization()
{
	FONT_Init();	// Characters and symbols initialization to draw on screen.

	render->TexturesSetting();
	render->RenderSetUp();
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.
	render->RenderObjects();
	render->RenderText();
	// Exchanges the front and back buffers
	SYS_Show();
}