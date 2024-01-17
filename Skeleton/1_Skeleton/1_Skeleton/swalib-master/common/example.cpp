#include "sys.h"
#include "gameLogic.h"
#include "render.h"

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
