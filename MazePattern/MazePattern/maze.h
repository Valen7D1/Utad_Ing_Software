#pragma once
#include <iostream>
#include "door.h"
#include "wall.h"
#include "room.h"
#include "factory.h"


class Maze {
public:
	// vector of rooms in maze
	std::vector<Room*> mazeMap; 
	void addRoom(Room* room);

	// iterate to delete all room values
	// then deletes all rooms
	void cleanUp();
	
	~Maze() { cleanUp(); } //destructor
};



class MazeGame {
public:
	MazeGame(){} //constructor

	Maze* myMaze = nullptr;

	void printMaze();
	//calls the iterator that creates the maze rooms
	// and sets their inner parameters and refs
	void generateMaze(factoryBase* factory);
	void cleanUp() { delete myMaze; }

    ~MazeGame() { //destructor
		cleanUp();
		myMaze = nullptr;
    }
};

