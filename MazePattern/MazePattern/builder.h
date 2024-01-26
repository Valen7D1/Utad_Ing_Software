#pragma once
#include "door.h"
#include "wall.h"
#include "room.h"
#include "factory.h"

// the difference between both maze builders
// is that one expands east to west
// and the other north to south

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




class BuilderBase {

public:
	BuilderBase(factoryBase* _factory): factory(_factory), myMaze(nullptr) {}
	virtual void BuildMaze() = 0; // builder virtual method for children
	Maze* getMyMaze() { return myMaze; } // * getter
	// iterates thorugh the myMaze to delete all objs except rooms 
	// and then does delete room for each
	~BuilderBase() 
	{ 
		cleanUp();
		myMaze = nullptr;
	}

protected:
	// maze and factory for children builders
	Maze* myMaze;
	factoryBase* factory;

private:
	// calls to the myMaze destructor
	//and sets myMaze to nullptr
	void cleanUp();
};


class BuilderEW : public BuilderBase
{
public:
	//constructor calls father constructor
	BuilderEW(factoryBase* factory): BuilderBase(factory){}
	// creates all the maze parts with the factory 
	void BuildMaze() override;
};

class BuildMazeNS : public BuilderBase
{
public:
	//constructor calls father constructor
	BuildMazeNS(factoryBase* factory) : BuilderBase(factory) {}
	// creates all the maze parts with the factory 
	void BuildMaze() override;
};