#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "../swalib_example/Code/Game/global.h"
#include "../swalib_example/Code/Game/logic.h"
#include "../swalib_example/Code/Game/render.h"

//-----------------------------------------------------------------------------
int Main(void)
{
	// Initialization.
	InitRender();
	InitGlobalData();

	// Main loop.
	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
		LogicSlot();	// Logic slot.

		RenderSlot();	// Render slot.
   
		SYS_Pump();	// Process Windows messages.
		SYS_Sleep(17);	// To force 60 fps
	}

	// Shutdown. In reverse order to initilization.
	ShutDownGlobalData();
	ShutDownRender();

	return 0;
}
