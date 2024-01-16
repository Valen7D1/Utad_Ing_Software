#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "gameLogic.h"
#include "render.h"

//va a ocurrir un error 1
//otra vez jeje2
int Main(void)
{	
	RenderInitialization();
	LogicInitialization();

	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
		// 2.1 va mucho mas rapido todo
		timeControl();

		Render();

		SYS_Pump();	// Process Windows messages.
	}

	Shutdown();

	return 0;
}
