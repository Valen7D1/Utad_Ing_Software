#include <iostream>
#include "maze.h"

// perdon tengo dislexia
// west es derecha
// east es izquierda
// north es arriba
// south es abajo

//XXXXX
//X | X
//XXXXX
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
	Room* room4 = new ExplosiveRoom(4);

	myMaze->addRoom(room1);
	myMaze->addRoom(room2);
	myMaze->addRoom(room3);
	myMaze->addRoom(room4);

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
	room4->setRoom(Direction::EAST, new Wall());
	room4->setRoom(Direction::WEST, new DestructibleWall(room1));

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
	/*std::vector<Room*> mazeMap;
	Room* room1 = new Room(1);
	mazeMap.push_back(room1);*/
	MazeGame maze1;
	maze1.generateMaze();
	maze1.printMaze();
}
