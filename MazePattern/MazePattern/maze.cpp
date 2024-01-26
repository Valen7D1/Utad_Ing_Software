#include <iostream>
#include "maze.h"

// perdon tengo dislexia
// west es derecha
// east es izquierda
// north es arriba
// south es abajo

//XXXXXXX
//X  |  X
//XXXXXXX
void Maze::addRoom(Room* room) 
{
	mazeMap.push_back(room);
}

void Maze::cleanUp() 
{
	for (Room* room : mazeMap) {
		room->cleanUp();
	}
	for (Room* room : mazeMap) {
		delete room;
	}
}


void MazeGame::generateMaze()
{
	_builder->BuildMaze();
}


void MazeGame::printMaze() const
{
	Maze* myMaze = _builder->getMyMaze();
	for (Room* room : myMaze->mazeMap) {
		printf("Room %d:\n", room->roomId);
		room->printRoom();
		printf("\n");
	}
}


int main() 
{
	printf("Factory Destructiva:\n");
	factoryDestroy myFactory1;
	BuilderBase* builderEW = new BuilderEW(&myFactory1);
	MazeGame* maze1 = new MazeGame(builderEW);

	maze1->printMaze();
	delete maze1;


	printf("Factory Explosiva:\n");
	factoryExplode myFactory2;
	BuilderBase* builderNS = new BuildMazeNS(&myFactory2);
	MazeGame* maze2 = new MazeGame(builderNS);

	maze2->printMaze();
	delete maze2;
}
