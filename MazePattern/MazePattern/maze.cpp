#include <iostream>
#include "maze.h"

// perdon tengo dislexia
// west es derecha
// east es izquierda
// north es arriba
// south es abajo


void Maze::addRoom(Room room) 
{
	mazeMap.push_back(&room);
}


void MazeGame::generateMaze() 
{
	Room* room1 = new Room(1);
	Room* room2 = new Room(2);

	/*room1->setRoom(Direction::NORTH, new Wall());
	room1->setRoom(Direction::SOUTH, new Wall());
	room1->setRoom(Direction::EAST, new Door(room2));
	room1->setRoom(Direction::WEST, new Wall());

	room2->setRoom(Direction::NORTH, new Wall());
	room2->setRoom(Direction::SOUTH, new Wall());
    room2->setRoom(Direction::EAST, new Wall()); 
	room2->setRoom(Direction::WEST, new Door(room1));*/

}


void MazeGame::printMaze() 
{
	for (const Room* room : myMaze->mazeMap) {
		room->print();
	}
}


int main() 
{
	MazeGame maze1;
	maze1.generateMaze();
	maze1.printMaze();
}
