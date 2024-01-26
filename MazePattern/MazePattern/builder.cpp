#include "builder.h"


void BuilderBase::cleanUp()
{
	myMaze->cleanUp();
	myMaze = nullptr;
}


void BuilderEW::BuildMaze()
{
	myMaze = new Maze();

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


void BuildMazeNS::BuildMaze()
{
	myMaze = new Maze();

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

	room2->setRoom(Direction::NORTH, room1);
	room2->setRoom(Direction::SOUTH, factory->CreateDoor(room3));
	room2->setRoom(Direction::EAST, factory->CreateWall());
	room2->setRoom(Direction::WEST, factory->CreateWall());

	room3->setRoom(Direction::NORTH, factory->CreateDoor(room2));
	room3->setRoom(Direction::SOUTH, factory->CreateWall());
	room3->setRoom(Direction::EAST, factory->CreateWall());
	room3->setRoom(Direction::WEST, factory->CreateWall());
}