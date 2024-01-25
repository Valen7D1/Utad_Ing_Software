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


void MazeGame::generateMaze(factoryBase* factory)
{
	myMaze = new Maze();
	factoryDestroy destructivos;
	factoryExplode explosivos;

	Room* room1 = factory->CreateRoom(1);
	Room* room2 = factory->CreateRoom(2);
	Room* room3 = factory->CreateRoom(3);

	myMaze->addRoom(room1);
	myMaze->addRoom(room2);
	myMaze->addRoom(room3);

	room1->setRoom(Direction::NORTH, factory->CreateWall());
	room1->setRoom(Direction::SOUTH, factory->CreateWall());
	room1->setRoom(Direction::EAST, factory->CreateWall());
	room1->setRoom(Direction::WEST, room2);

	room2->setRoom(Direction::NORTH, factory->CreateWall());
	room2->setRoom(Direction::SOUTH, factory->CreateWall());
    room2->setRoom(Direction::EAST, room1); 
	room2->setRoom(Direction::WEST, factory->CreateDoor(room3));

	room3->setRoom(Direction::NORTH, factory->CreateWall());
	room3->setRoom(Direction::SOUTH, factory->CreateWall());
	room3->setRoom(Direction::EAST, factory->CreateDoor(room2));
	room3->setRoom(Direction::WEST, factory->CreateWall());

}


void MazeGame::printMaze() 
{
	for (Room* room : myMaze->mazeMap) {
		printf("Room %d:\n", room->roomId);
		room->printRoom();
		printf("\n");
	}
}


int main() 
{
	printf("Factory Destructiva:\n");
	MazeGame* maze1 = new MazeGame();
	factoryDestroy myFactory1;

	maze1->generateMaze(&myFactory1);
	maze1->printMaze();
	delete maze1;

	printf("Factory Explosiva:\n");
	MazeGame* maze2 = new MazeGame();
	factoryExplode myFactory2;

	maze2->generateMaze(&myFactory2);
	maze2->printMaze();
	delete maze2;
}
