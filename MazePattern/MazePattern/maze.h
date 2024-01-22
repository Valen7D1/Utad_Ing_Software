#pragma once
#include <iostream>
#include <vector>
#include "door.h"
#include "wall.h"
#include "room.h"


class Maze {
	std::vector<mapSite*> mazeMap;
	void addRoom();
};



class MazeGame {
public:
	MazeGame* myMaze;

	void printMaze();
	void generateMaze();
};

