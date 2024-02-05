#include "sys.h"
#include "gameLogic.h"
#include "render.h"
#include <iostream>
#include "../swalib_example/rapidjson/document.h"
#include "../swalib_example/rapidjson/filereadstream.h"

int Main(void)
{	
	//RenderInitialization();
	//LogicInitialization();

	//while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
	//	
	//	LogicSlot(); // call to logic control

	//	Render(); // call to render

	//	SYS_Pump();	// Process Windows messages.
	//}

	//Shutdown();

	char readBuffer[1024];
	FILE* fp;
	fopen_s(&fp, "data/test.json", "rb");
	if (!fp) {
		std::cerr << "Error al abrir el archivo de las bolas." << std::endl;
		return -1;
	}
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	// 3. Convierte el buffer en un Documento
	rapidjson::Document document;
	document.ParseStream(is);
	for (int i = 0; i < sizeof(readBuffer); i++) {
		printf("%c", i);
	}


	return 0;
}
