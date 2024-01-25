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

	~Maze() {
		for (Room* room : mazeMap) {
			room->cleanUp();
			//room = nullptr;
		}
		for (Room* room : mazeMap) {
			delete room;
		}
	}
};



class MazeGame {
public:
	MazeGame(){}

	Maze* myMaze = nullptr;

	void printMaze();
	void generateMaze();

    ~MazeGame() {
		delete myMaze;
    }
};

