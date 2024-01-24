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


void MazeGame::generateMaze() 
{
	myMaze = new Maze();

	Room* room1 = new Room(1);
	Room* room2 = new Room(2);
	Room* room3 = new Room(3);
	Room* room4 = new Room(4);
	Room* room5 = new ExplosiveRoom(5);

	myMaze->addRoom(room1);
	myMaze->addRoom(room2);
	myMaze->addRoom(room3);
	myMaze->addRoom(room4);
	myMaze->addRoom(room5);

	room1->setRoom(Direction::NORTH, new Wall());
	room1->setRoom(Direction::SOUTH, new Wall());
	room1->setRoom(Direction::EAST, new DestructibleWall(room4));
	room1->setRoom(Direction::WEST, room2);

	room2->setRoom(Direction::NORTH, new Wall());
	room2->setRoom(Direction::SOUTH, new Wall());
    room2->setRoom(Direction::EAST, room1); 
	room2->setRoom(Direction::WEST, new Door(room3));

	room3->setRoom(Direction::NORTH, new Wall());
	room3->setRoom(Direction::SOUTH, new Wall());
	room3->setRoom(Direction::EAST, new Door(room2));
	room3->setRoom(Direction::WEST, new Wall());

	room4->setRoom(Direction::NORTH, new Wall());
	room4->setRoom(Direction::SOUTH, new Wall());
	room4->setRoom(Direction::EAST, room5);
	room4->setRoom(Direction::WEST, new DestructibleWall(room1));

	room5->setRoom(Direction::NORTH, new Wall());
	room5->setRoom(Direction::SOUTH, new Wall());
	room5->setRoom(Direction::EAST, room4);
	room5->setRoom(Direction::WEST, new Wall());

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
	MazeGame maze1;
	maze1.generateMaze();
	maze1.printMaze();
}
