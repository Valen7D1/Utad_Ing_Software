#include "sys.h"
#include "gameLogic.h"
#include "render.h"

int Main(void)
{	
	RenderInitialization();
	LogicInitialization();

	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
		
		LogicSlot(); // call to logic control

		Render(); // call to render

		SYS_Pump();	// Process Windows messages.
	}

	Shutdown();

	return 0;
}
