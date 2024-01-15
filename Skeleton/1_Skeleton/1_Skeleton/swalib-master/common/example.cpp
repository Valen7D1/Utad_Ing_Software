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

		timeControl();

		Render();

		SYS_Pump();	// Process Windows messages.
	}

	Shutdown();

	return 0;
}
