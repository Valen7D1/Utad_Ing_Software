#pragma once
#include <iostream>
#include "door.h"
#include "wall.h"
#include "room.h"


class Maze {
public:
	//Room* mazeMap[2];
	std::vector<Room*> mazeMap;
	void addRoom(Room* room);
};



class MazeGame {
public:
	Maze* myMaze = nullptr;

	void printMaze();
	void generateMaze();
};

