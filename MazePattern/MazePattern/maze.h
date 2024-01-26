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

	void printMaze() const;

    ~MazeGame() { //destructor
		cleanUp();
		_builder = nullptr;
    }
private:
	BuilderBase* _builder;

	// calls to the builder buildMaze method
	void generateMaze();
	// calls to builder destructor
	void cleanUp() { delete _builder; }
};

