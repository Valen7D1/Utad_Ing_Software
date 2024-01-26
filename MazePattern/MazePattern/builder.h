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
	virtual void BuildMaze() = 0;
	Maze* getMyMaze() { return myMaze; }
	~BuilderBase() { cleanUp(); }

protected:
	Maze* myMaze;
	factoryBase* factory;

private:
	void cleanUp();
};


class BuilderEW : public BuilderBase
{
public:
	BuilderEW(factoryBase* factory): BuilderBase(factory){}

	void BuildMaze() override;
};

class BuildMazeNS : public BuilderBase
{
public:
	BuildMazeNS(factoryBase* factory) : BuilderBase(factory) {}

	void BuildMaze() override;
};