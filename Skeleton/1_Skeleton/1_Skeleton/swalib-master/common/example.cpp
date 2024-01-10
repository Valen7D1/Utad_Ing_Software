#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "gameLogic.h"
#include "render.h"


int Main(void)
{	
	RenderInitialization();
	LogicInitialization();

	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
		ProcessGameLogic();
		Render();

		SYS_Pump();	// Process Windows messages.
		SYS_Sleep(17);	// To force 60 fps
	}

	Shutdown();

	return 0;
}
