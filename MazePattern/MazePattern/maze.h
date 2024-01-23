#pragma once
#include <iostream>
#include "door.h"
#include "wall.h"
#include "room.h"


class Maze {
public:
	std::vector<Room*> mazeMap;
	void addRoom(Room room);
};



class MazeGame {
public:
	Maze* myMaze;

	void printMaze();
	void generateMaze();
};

