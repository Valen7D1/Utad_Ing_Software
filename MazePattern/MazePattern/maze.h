#pragma once
#include <iostream>
#include "factory.h"
#include "builder.h"

class MazeGame {
public:
	MazeGame(BuilderBase* builder) : _builder(builder) 
	{ 
		generateMaze(); //we generate the maze in construction
	}

	BuilderBase* _builder = nullptr;

	void printMaze() const;
	//calls the iterator that creates the maze rooms
	// and sets their inner parameters and refs

    ~MazeGame() { //destructor
		cleanUp();
		_builder = nullptr;
    }
private:
	void generateMaze();
	void cleanUp() { delete _builder; }
};

